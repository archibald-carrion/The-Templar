#include "game.hpp"
#include <iostream>

#include "../systems/render_system.hpp"
#include "../systems/movement_system.hpp"
#include "../systems/circle_collision_system.hpp"
#include "../systems/animation_system.hpp"
#include "../systems/script_system.hpp"
#include "../systems/render_text_system.hpp"
#include "../systems/UI_system.hpp"
#include "../systems/camera_movement_system.hpp"
#include "../systems/box_collision_system.hpp"
#include "../systems/render_box_collider_system.hpp"
#include "../systems/render_damage_collider_system.hpp"
#include "../systems/player_score_system.hpp"
#include "../systems/PhysicsSystem.hpp"
#include "../systems/overlap_system.hpp"
#include "../systems/cooldowns_system.hpp"
#include "../systems/damage_collision_system.hpp"
#include "../systems/lifetime_system.hpp"
#include "../systems/render_circular_collider_system.hpp"
#include "../systems/enemy_attack_system.hpp"
#include "../systems/enemy_collider_system.hpp"
#include "../systems/render_enemy_collider_system.hpp"
#include "../systems/stats_system.hpp"

#include "../events/click_event.hpp"

Game::Game() :
sdl_manager(SDLManager::getInstance())
, registry(std::make_unique<Registry>())
, scene_manager(std::make_unique<SceneManager>())
, assets_manager(std::make_unique<AssetsManager>())
, events_manager(std::make_unique<EventManager>())
, controller_manager(std::make_unique<ControllerManager>())
, audio_manager(std::make_unique<AudioManager>())
, animation_manager(std::make_unique<AnimationManager>()) {
    //std::cout << "[GAME] Constructor" << std::endl;
    if (!sdl_manager.isValid()) {
        throw std::runtime_error("Failed to initialize SDL");
    }
}

Game::~Game() {
    //std::cout << "[GAME] Destructor" << std::endl;
}

void Game::setup() {
    registry->add_system<RenderSystem>();
    registry->add_system<MovementSystem>();
    registry->add_system<CircleCollisionSystem>();
    registry->add_system<AnimationSystem>();
    registry->add_system<ScriptSystem>();
    registry->add_system<RenderTextSystem>();
    registry->add_system<UISystem>();
    registry->add_system<CameraMovementSystem>();
    registry->add_system<BoxCollisionSystem>();
    registry->add_system<PlayerScoreSystem>();
    registry->add_system<RenderBoxColliderSystem>();
    registry->add_system<PhysicsSystem>();
    registry->add_system<OverlapSystem>();
    registry->add_system<CooldownsSystem>();
    registry->add_system<DamageCollisionSystem>();
    registry->add_system<RenderDamageColliderSystem>();
    registry->add_system<LifetimeSystem>();
    registry->add_system<RenderCircularColliderSystem>();
    registry->add_system<EnemyAttackSystem>();
    registry->add_system<EnemyCollisionSystem>();
    registry->add_system<RenderEnemyColliderSystem>();
    registry->add_system<StatsSystem>();

    scene_manager->load_scene_from_script("assets/scripts/scenes.lua", lua);

    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string);
    registry->get_system<ScriptSystem>().create_lua_binding(lua);
}

Game& Game::get_instance() {
    static Game game;
    return game;
}

void Game::init() {
    //std::cout << "[GAME] Init" << std::endl;

    // create the window
    this->window = SDL_CreateWindow(
        "De Astra, Ad Terra",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    SDL_SetWindowResizable(window, SDL_FALSE);

    // create renderer
    this->renderer = SDL_CreateRenderer(
        this->window, 
        -1, // screen driver index
        0 // no flags
    );

    camera.x = 0;
    camera.y = 0;
    camera.w = WINDOW_WIDTH;
    camera.h = WINDOW_HEIGHT;

    this->isRunning = true;

    std::cout << "Controllers found: " << SDL_NumJoysticks() << std::endl;

    for (int current = 0; current < SDL_NumJoysticks(); current++) {
        if (SDL_IsGameController(current)) {
            std::unique_ptr<SDL_GameController, decltype(controllerDeleter)> controller;
            controller.reset(SDL_GameControllerOpen(current));
            if (controller) {
                controllers.push_back(std::move(controller));
            } else
            {
                std::cout << "Controller does not exist" << std::endl;
            }
        }
    }
}

void Game::run() {
    setup();

    while (isRunning) {
        scene_manager->start_scene();
        run_scene();
    }
}

void Game::run_scene() {
    scene_manager->load_scene();
    registry->update();
    // call the on_init functions of the entities from the script component
    registry->get_system<ScriptSystem>().init_from_script(lua);
    this->player_score = 0; // reset score between levels

    while(scene_manager->is_current_scene_running()) {
        processInput();
        update();
        render();
    }

    assets_manager->clear_assets();
    registry->clear_all_entities();
}

void Game::destroy() {
    lua = sol::state();

    // stop all currently playing sounds
    Mix_HaltChannel(-1);  // -1 means all channels

    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
}

void Game::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // close the window events
            case SDL_QUIT:
                scene_manager->stop_scene();
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    scene_manager->stop_scene();
                    isRunning = false;
                    break;
                } else if (event.key.keysym.sym == SDLK_p)
                {
                    isPaused = !isPaused;
                    break;
                }
                if (event.key.keysym.sym == SDLK_i)
                {
                    // toggle is_debug_mode_activated
                    is_debug_mode_activated = !is_debug_mode_activated;
                    break;
                }
                controller_manager->set_key_to_pressed(event.key.keysym.sym);          
                break;

            case SDL_KEYUP:
                controller_manager->set_key_to_up(event.key.keysym.sym);
                break;

            case SDL_MOUSEMOTION:
                int x, y;
                SDL_GetMouseState(&x, &y);
                controller_manager->set_mouse_position(x, y);
                break;

            case SDL_MOUSEBUTTONDOWN:
                controller_manager->set_mouse_position(event.button.x, event.button.y);
                controller_manager->set_mouse_button_to_pressed(static_cast<int>(event.button.button));
                events_manager->emit_event<ClickEvent>(static_cast<int>(event.button.button), event.button.x, event.button.y);
                break;

            case SDL_MOUSEBUTTONUP:
                controller_manager->set_mouse_position(event.button.x, event.button.y);
                controller_manager->set_mouse_button_to_up(static_cast<int>(event.button.button));
                break;

            case SDL_CONTROLLERBUTTONDOWN:
                {
                switch (event.cbutton.button)
                {
                    case 13: // left
                        controller_manager->set_key_to_pressed(97);
                        break;
                    case 14: // right
                        controller_manager->set_key_to_pressed(100);
                        break;
                    case SDL_CONTROLLER_BUTTON_A:
                        controller_manager->set_key_to_pressed(SDLK_SPACE);
                        break;
                    case SDL_CONTROLLER_BUTTON_B:
                        controller_manager->set_key_to_pressed(SDLK_e);
                        break;
                    case SDL_CONTROLLER_BUTTON_X:
                        isPaused = !isPaused;
                        break;
                    case SDL_CONTROLLER_BUTTON_Y:
                        controller_manager->set_key_to_pressed(SDLK_q);
                        break;
                    default:
                        break;
                }
                break;
                }
            case SDL_CONTROLLERBUTTONUP:
                switch (event.cbutton.button)
                {
                    case 13: // left
                        controller_manager->set_key_to_up(97);
                        break;
                    case 14: // right
                        controller_manager->set_key_to_up(100);
                        break;
                    case SDL_CONTROLLER_BUTTON_A:
                        controller_manager->set_key_to_up(SDLK_SPACE);
                        break;
                    case SDL_CONTROLLER_BUTTON_B:
                        controller_manager->set_key_to_up(SDLK_e);
                        break;
                    case SDL_CONTROLLER_BUTTON_X:
                        break;
                    case SDL_CONTROLLER_BUTTON_Y:
                        controller_manager->set_key_to_up(SDLK_q);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_CONTROLLERAXISMOTION:
                break;
            default:
                break;
        }
    }
}

void Game::update() {

    if (isPaused) {
        this->mPreviousFrame = SDL_GetTicks();
        return;
    }

    if (const uint32_t time_to_wait = MILLISECS_PER_FRAME - (SDL_GetTicks() - this->mPreviousFrame);
        time_to_wait > 0 && time_to_wait <= MILLISECS_PER_FRAME) {
        SDL_Delay(time_to_wait);
    }

    // calculate the time between frames
    const double deltaTime = (SDL_GetTicks() - this->mPreviousFrame) / 1000.0;
    this->mPreviousFrame = SDL_GetTicks();

    // re-initialize subscriptions
    events_manager->reset();

    registry->get_system<OverlapSystem>().SubscribeToCollisionEvent(events_manager);
    registry->get_system<UISystem>().suscribe_to_click_event(events_manager);

    registry->update();
    registry->get_system<ScriptSystem>().update(lua);
    registry->get_system<AnimationSystem>().update();

    registry->get_system<PhysicsSystem>().update();

    registry->get_system<MovementSystem>().update(deltaTime);

    registry->get_system<BoxCollisionSystem>().update(this->events_manager, lua);
    registry->get_system<CircleCollisionSystem>().update(events_manager, lua);
    registry->get_system<DamageCollisionSystem>().update(*events_manager, lua);
    registry->get_system<EnemyCollisionSystem>().update(events_manager, lua);

    registry->get_system<CooldownsSystem>().update(deltaTime);

    registry->get_system<CameraMovementSystem>().update(this->camera);
    registry->get_system<LifetimeSystem>().update(deltaTime);
    registry->get_system<EnemyAttackSystem>().update(lua);


}

void Game::render() {
    SDL_RenderClear(this->renderer);

    // render all renderable systems
    registry->get_system<RenderSystem>().update(renderer, assets_manager, this->camera);
    registry->get_system<PlayerScoreSystem>().update(renderer, player_score);
    registry->get_system<RenderTextSystem>().update(renderer, assets_manager);

    registry->get_system<StatsSystem>().update(renderer);

    if (is_debug_mode_activated){
        registry->get_system<RenderBoxColliderSystem>().update(renderer, this->camera);
        registry->get_system<RenderDamageColliderSystem>().update(renderer, this->camera);
        registry->get_system<RenderCircularColliderSystem>().update(renderer, this->camera);
        registry->get_system<RenderEnemyColliderSystem>().update(renderer, this->camera);
    }

    SDL_RenderPresent(this->renderer);
}
