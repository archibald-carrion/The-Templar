#include "scene_manager.hpp"
#include <iostream>
#include "../game/game.hpp"

SceneManager::SceneManager() {
    // std::cout << "[SCENEMANAGER] Constructor" << std::endl;
    this->scene_loader = std::make_unique<SceneLoader>();
}

SceneManager::~SceneManager() {
    scene_loader.reset();
    // std::cout << "[SCENEMANAGER] Destructor" << std::endl;
}

void SceneManager::load_scene_from_script(const std::string& scene_path, sol::state& lua) {
    lua.script_file(scene_path);
    sol::table scenes = lua["scenes"];
    int index = 0;
    while(true) {
        sol::optional<sol::table> has_scene = scenes[index];
        if(has_scene == sol::nullopt) {
            break;
        }

        sol::table scene = scenes[index];
        this->scenes.emplace(scene["name"], scene["path"]);

        if (index == 0) {
            this->next_scene = scene["name"];
        }

        index++;
        
    }
}

void SceneManager::load_scene() {
    Game& game = Game::get_instance();
    std::string scene_path = scenes[next_scene];

    // std::cout << "[SCENEMANAGER] loading new scene" << std::endl;

    scene_loader->load_scene(scene_path, game.lua, game.assets_manager, game.controller_manager, game.audio_manager, game.registry,game.animation_manager, game.renderer);
}

std::string SceneManager::get_next_scene() const{
    return this->next_scene;
}

void SceneManager::set_next_scene(const std::string& next_scene) {
    this->next_scene = next_scene;
}

bool SceneManager::is_current_scene_running() const {
    return this->is_scene_running;
}
    
void SceneManager::start_scene() {
    this->is_scene_running = true;
}
    
void SceneManager::stop_scene() {
    this->is_scene_running = false;
}