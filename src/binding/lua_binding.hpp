#ifndef LUA_BINDING_HPP
#define LUA_BINDING_HPP

#include <string> // used for strings
#include <tuple> // used for returning multiple values
#include <SDL2/SDL.h> // SDL library for window creation and rendering
#include "../ECS/ECS.hpp" // ECS library for entity-component-system
#include "../game/game.hpp" // Game class for getting the game instance
#include "../components/RigidBodyComponent.hpp" // RigidBodyComponent for adding rigid body to entities
#include "../components/box_collider_component.hpp" // BoxColliderComponent for adding box collider to entities
#include "../components/sprite_component.hpp" // SpriteComponent for adding sprite to entities
#include "../components/transform_component.hpp" // TransformComponent for adding transform to entities
#include "../components/tag_component.hpp" // TagComponent for adding tag to entities
#include "../components/player_velocity.hpp" // PlayerVelocity for adding player velocity to entities
#include "../components/lifetime_component.hpp" // LifetimeComponent for adding lifetime to entities
#include "../components/player_score_component.hpp" // PlayerScore for adding player score to entities
#include "../animation_manager/animation_manager.hpp" // AnimationManager for managing animations
#include "../components/cooldown_component.hpp" // CooldownComponent for adding cooldown to entities
#include "../components/damage_collider_component.hpp" // DamageColliderComponent for adding damage collider to entities
#include "../components/state_component.hpp" // StateComponent for adding state to entities
#include "../components/father_component.hpp" // FatherComponent for adding father to entities
#include "../components/child_component.hpp" // ChildComponent for adding child to entities
#include "../components/stats_component.hpp" // StatsComponent for adding stats to entities



#pragma region Entity Management Functions

/**
 * @brief Kill an entity.
 * @param e The entity to kill.
 */
void kill_entity(Entity e)
{
    e.kill();
}

/**
 * @brief Get the tag of an entity.
 * @param e The entity to get the tag from.
 * @return The tag of the entity.
 */
std::string get_tag(Entity entity)
{
    return entity.get_component<TagComponent>().tag;
}

/**
 * @brief Get the class of an entity.
 * @param e The entity to get the class from.
 * @return The class of the entity.
 */
std::string get_class(Entity entity)
{
    return entity.get_component<TagComponent>().e_class;
}

#pragma endregion Entity Management Functions

#pragma region Animation and Sprite Functions

/**
 * @brief Change the animation of an entity.
 * @param entity The entity to change the animation for.
 * @param animationId The ID of the animation to change to.
 */
void change_animation(Entity entity, const std::string &animationId)
{
    auto &animation = entity.get_component<AnimationComponent>();
    auto &sprite = entity.get_component<SpriteComponent>();

    const AnimationData animationData = Game::get_instance().animation_manager->get_animation(
        animationId);

    sprite.texture_id = animationData.texture_id;
    sprite.width = animationData.width;
    sprite.height = animationData.height;

    sprite.src_rect.x = 0;
    sprite.src_rect.y = 0;
    sprite.src_rect.w = sprite.width;
    sprite.src_rect.h = sprite.height;

    animation.current_frame = 1;
    animation.frame_speed_rate = animationData.frame_speed_rate;
    animation.num_frames = animationData.num_frames;
    animation.is_loop = animationData.is_loop;
    animation.start_time = SDL_GetTicks();
}

/**
 * @brief Get the current animation frame of an entity.
 * @param entity The entity to get the animation frame from.
 * @return The current animation frame of the entity.
 */
int get_animation_frame(Entity entity)
{
    auto &animation = entity.get_component<AnimationComponent>();
    return animation.current_frame;
}

/**
 * @brief Flip the sprite of an entity.
 * @param e The entity to flip the sprite for.
 * @param flip True to flip the sprite, false otherwise.
 */
void flip_sprite(Entity entity, bool flip)
{
    auto &sprite = entity.get_component<SpriteComponent>();
    sprite.flip = flip;
}

/**
 * @brief Check if the sprite is looking right.
 * @param e The entity to check the sprite for.
 * @return True if the sprite is looking right, false otherwise.
 */
bool looking_right(Entity entity)
{
    if (!entity.has_component<SpriteComponent>())
        return false;

    return entity.get_component<SpriteComponent>().flip;
}

/**
 * @brief Get the size of an entity.
 * @param e The entity to get the size from.
 * @return A tuple containing the width and height of the entity.
 */
std::tuple<int, int> get_size(Entity e)
{
    const auto &sprite = e.get_component<SpriteComponent>();
    const auto &transform = e.get_component<TransformComponent>();

    int width = sprite.width * transform.scale.x;
    int height = sprite.height * transform.scale.y;

    return {width, height};
}

#pragma endregion Animation and Sprite Functions

#pragma region Projectile and Shooting Functions

/**
 * @brief Shoot a fireball from the player entity.
 * @param entity The entity to shoot the fireball from.
 */
void shoot_fireball(Entity entity)
{
    // std::cout << "[LUABINDING] creating new fireball" << std::endl;
    //  Get the registry instance to create new entity
    auto &registry = Game::get_instance().registry;

    // Create new fireball entity
    Entity fireball = registry->create_entity();

    // Get player position, rotation and sprite info
    const auto &player_transform = entity.get_component<TransformComponent>();

    // Add components to fireball entity
    fireball.add_component<BoxColliderComponent>(
        8,              // width
        8,              // height
        glm::vec2(0, 0) // offset
    );

    fireball.add_component<SpriteComponent>(
        "fireball", // asset_id
        64,         // width
        64,         // height
        0,          // src_rect.x
        0           // src_rect.y
    );

    fireball.add_component<TagComponent>("fireball");

    // add rigidbody component to either shoot left or right
    fireball.add_component<RigidBodyComponent>(
        true, false, 0 // is_dynamic, is_solid, mass
    );

    fireball.add_component<TransformComponent>(
        glm::vec2(player_transform.position.x, player_transform.position.y), // position (at nose, offset by half bullet size)
        glm::vec2(1.0f, 1.0f),                                               // scale
        0                                                                    // rotation (match player rotation)
    );

    auto &rigidBody = fireball.get_component<RigidBodyComponent>();
    rigidBody.velocity.x = entity.get_component<RigidBodyComponent>().velocity.x;
    rigidBody.velocity.y = 0;
}

/**
 * @brief Create a projectile entity.
 * @param father The entity to create the projectile from.
 * @param tag The tag of the projectile.
 * @param x_offset The x offset of the projectile.
 * @param y_offset The y offset of the projectile.
 * @param rotation The rotation of the projectile.
 * @param velocity_x The x velocity of the projectile.
 * @param velocity_y The y velocity of the projectile.
 * @param width The width of the projectile.
 * @param height The height of the projectile.
 * @param ticks_alive The number of ticks the projectile should be alive.
 * @param followFather Whether the projectile should follow the father entity.
 */
void create_projectile(Entity father, std::string tag, int32_t x_offset, int32_t y_offset, double rotation, double velocity_x, double velocity_y, int32_t width, int32_t height, double ticks_alive, bool followFather = false)
{
    Entity projectile = father.registry->create_entity();
    auto fatherTransform = father.get_component<TransformComponent>();

    // transform component : position
    projectile.add_component<TransformComponent>(
        followFather ? glm::vec2{0, 0}
                     : glm::vec2{fatherTransform.position.x + x_offset, fatherTransform.position.y + y_offset},
        fatherTransform.scale,
        rotation);

    // rigidbody component : direction
    projectile.hot_add_component<RigidBodyComponent>();
    auto &rigidbody = projectile.get_component<RigidBodyComponent>();
    rigidbody.velocity.x = velocity_x;
    rigidbody.velocity.y = velocity_y;
    rigidbody.default_movement = true;

    if (followFather)
    {
        rigidbody.father = father;
        projectile.get_component<TransformComponent>().movement_offset =
            glm::vec2{x_offset, y_offset};
    }

    // damage collider : collision
    projectile.hot_add_component<DamageColliderComponent>(width, height);

    // lifetime : must die after time
    projectile.hot_add_component<LifetimeComponent>(ticks_alive);

    // tag: must identify when colliding
    projectile.hot_add_component<TagComponent>(tag, father.get_component<TagComponent>().e_class);

    if (father.has_component<FatherComponent>())
    {
        father.get_component<FatherComponent>().Children.push_back(projectile);
    }

    projectile.hot_add_component<ChildComponent>(father);

    StatsManager::GetInstance().AddStatsToEntity(projectile);
}

/**
 * @brief Create a projectile entity with an animation.
 * @param father The entity to create the projectile from.
 * @param tag The tag of the projectile.
 * @param x_offset The x offset of the projectile.
 * @param y_offset The y offset of the projectile.
 * @param rotation The rotation of the projectile.
 * @param velocity_x The x velocity of the projectile.
 * @param velocity_y The y velocity of the projectile.
 * @param width The width of the projectile.
 * @param height The height of the projectile.
 * @param ticks_alive The number of ticks the projectile should be alive.
 * @param followFather Whether the projectile should follow the father entity.
 * @param animation The animation of the projectile.
 * @param scale The scale of the projectile.
 */
void create_projectile_with_animation(Entity father, std::string tag, int32_t x_offset, int32_t y_offset, double rotation, double velocity_x, double velocity_y, int32_t width, int32_t height, double ticks_alive, bool followFather = false, std::string animation = "", float scale = 1)
{
    Entity projectile = father.registry->create_entity();
    auto fatherTransform = father.get_component<TransformComponent>();

    // transform component : position
    projectile.add_component<TransformComponent>(
        followFather ? glm::vec2{0, 0}
                     : glm::vec2{fatherTransform.position.x + x_offset, fatherTransform.position.y + y_offset},
        fatherTransform.scale * scale,
        rotation);

    // rigidbody component : direction
    projectile.hot_add_component<RigidBodyComponent>();
    auto &rigidbody = projectile.get_component<RigidBodyComponent>();
    rigidbody.velocity.x = velocity_x;
    rigidbody.velocity.y = velocity_y;
    rigidbody.default_movement = true;

    if (followFather)
    {
        rigidbody.father = father;
        projectile.get_component<TransformComponent>().movement_offset =
            glm::vec2{x_offset, y_offset};
    }

    // damage collider : collision
    projectile.hot_add_component<DamageColliderComponent>(width, height);

    // lifetime : must die after time
    projectile.hot_add_component<LifetimeComponent>(ticks_alive);

    // tag: must identify when colliding
    projectile.hot_add_component<TagComponent>(tag, father.get_component<TagComponent>().e_class);

    projectile.hot_add_component<AnimationComponent>();
    projectile.hot_add_component<SpriteComponent>();

    change_animation(projectile, animation);

    if (father.has_component<FatherComponent>())
    {
        father.get_component<FatherComponent>().Children.push_back(projectile);
    }

    projectile.hot_add_component<ChildComponent>(father);

    StatsManager::GetInstance().AddStatsToEntity(projectile);
}

#pragma endregion Projectile and Shooting Functions

#pragma region Rigid Body and Movement Functions

/**
 * @brief add_force to an entity.
 * @param entity The entity to add force to.
 * @param x The x component of the force.
 * @param y The y component of the force.
 */
void add_force(Entity entity, float x, float y)
{
    auto &rigidBody = entity.get_component<RigidBodyComponent>();
    rigidBody.sum_forces += glm::vec2(x, y);
}

/**
 * @brief Set the velocity of an entity.
 * @param e The entity to set the velocity for.
 * @param x The x component of the velocity.
 * @param y The y component of the velocity.
 */
void set_velocity(Entity e, float x, float y)
{
    auto &rigid_body = e.get_component<RigidBodyComponent>();
    rigid_body.velocity.x = x;
    rigid_body.velocity.y = y;
}

/**
 * @brief Get the velocity of an entity.
 * @param e The entity to get the velocity from.
 * @return A tuple containing the x and y components of the velocity.
 */
std::tuple<int, int> get_velocity(Entity e)
{
    const auto &rigid_body = e.get_component<RigidBodyComponent>();
    return {static_cast<int>(rigid_body.velocity.x), static_cast<int>(rigid_body.velocity.y)};
}

/**
 * @brief Get the buffered velocity of an entity.
 * @param e The entity to get the buffered velocity from.
 * @return A tuple containing the x and y components of the buffered velocity.
 */
std::tuple<int, int> get_buffered_velocity(Entity e)
{
    const auto &rigid_body = e.get_component<RigidBodyComponent>();
    auto velocity = rigid_body.velocity_buffer;
    return {static_cast<int>(velocity.x), static_cast<int>(velocity.y)};
}

/**
 * @brief Set the position of an entity.
 * @param e The entity to set the position for.
 * @param x The x coordinate of the position.
 * @param y The y coordinate of the position.
 */
void set_position(Entity e, int x, int y)
{
    auto &transform = e.get_component<TransformComponent>();
    transform.position.x = static_cast<float>(x);
    transform.position.y = static_cast<float>(y);
}

/**
 * @brief Get the position of an entity.
 * @param e The entity to get the position from.
 * @return A tuple containing the x and y coordinates of the entity.
 */
std::tuple<int, int> get_position(Entity e)
{
    const auto &transform = e.get_component<TransformComponent>();
    return {static_cast<int>(transform.position.x), static_cast<int>(transform.position.y)};
}

#pragma endregion Rigid Body and Movement Functions

#pragma region Collision and Physics Functions

/**
 * @brief Check if two entities are colliding from the top.
 * @param e The first entity.
 * @param other The second entity.
 * @return True if the entities are colliding from the top, false otherwise.
 */
bool top_collision(Entity e, Entity other)
{
    const auto &e_collider = e.get_component<BoxColliderComponent>();
    const auto &e_transform = e.get_component<TransformComponent>();
    const auto &other_collider = other.get_component<BoxColliderComponent>();
    const auto &other_transform = other.get_component<TransformComponent>();

    float e_x = e_transform.previous_position.x;
    float e_y = e_transform.previous_position.y;

    float e_w = static_cast<float>(e_collider.width);

    float other_x = other_transform.previous_position.x;
    float other_y = other_transform.previous_position.y;

    float other_w = static_cast<float>(other_collider.width);

    // check if left side of e is colliding with other
    return (
        other_x < e_x + e_w &&
        other_x + other_w > e_x &&
        other_y < e_y);
}

/**
 * @brief Check if two entities are colliding from the left.
 * @param e The first entity.
 * @param other The second entity.
 * @return True if the entities are colliding from the left, false otherwise.
 */
bool left_collision(Entity e, Entity other)
{
    const auto &e_collider = e.get_component<BoxColliderComponent>();
    const auto &e_transform = e.get_component<TransformComponent>();
    const auto &other_collider = other.get_component<BoxColliderComponent>();
    const auto &other_transform = other.get_component<TransformComponent>();

    float e_x = e_transform.previous_position.x;
    float e_y = e_transform.previous_position.y;

    float e_h = static_cast<float>(e_collider.height);

    float other_x = other_transform.previous_position.x;
    float other_y = other_transform.previous_position.y;

    float other_h = static_cast<float>(other_collider.height);

    // check if left side of e is colliding with other
    return (
        other_y < e_y + e_h &&
        other_y + other_h > e_y &&
        other_x < e_x);
}

/**
 * @brief Check if two entities are colliding from the bottom.
 * @param e The first entity.
 * @param other The second entity.
 * @return True if the entities are colliding from the bottom, false otherwise.
 */
bool bottom_collision(Entity e, Entity other)
{
    const auto &e_collider = e.get_component<BoxColliderComponent>();
    const auto &e_transform = e.get_component<TransformComponent>();
    const auto &other_collider = other.get_component<BoxColliderComponent>();
    const auto &other_transform = other.get_component<TransformComponent>();

    float e_x = e_transform.previous_position.x;
    float e_y = e_transform.previous_position.y;

    float e_w = static_cast<float>(e_collider.width);

    float other_x = other_transform.previous_position.x;
    float other_y = other_transform.previous_position.y;

    float other_w = static_cast<float>(other_collider.width);

    // check if left side of e is colliding with other
    return (
        other_x < e_x + e_w &&
        other_x + other_w > e_x &&
        other_y > e_y);
}

/**
 * @brief Check if two entities are colliding from the right.
 * @param e The first entity.
 * @param other The second entity.
 * @return True if the entities are colliding from the right, false otherwise.
 */
bool right_collision(Entity e, Entity other)
{
    const auto &e_collider = e.get_component<BoxColliderComponent>();
    const auto &e_transform = e.get_component<TransformComponent>();
    const auto &other_collider = other.get_component<BoxColliderComponent>();
    const auto &other_transform = other.get_component<TransformComponent>();

    float e_x = e_transform.previous_position.x;
    float e_y = e_transform.previous_position.y;

    float e_h = static_cast<float>(e_collider.height);

    float other_x = other_transform.previous_position.x;
    float other_y = other_transform.previous_position.y;

    float other_h = static_cast<float>(other_collider.height);

    // check if left side of e is colliding with other
    return (
        other_y < e_y + e_h &&
        other_y + other_h > e_y &&
        other_x > e_x);
}

/**
 * @brief set_box_collider of an entity.
 * @param entity The entity to set the box collider for.
 * @param width The width of the box collider.
 * @param height The height of the box collider.
 * @param offset_x The x offset of the box collider.
 * @param offset_y The y offset of the box collider.
 */
void set_box_collider(Entity entity, int width, int height, int offset_x, int offset_y)
{
    auto &box_collider = entity.get_component<BoxColliderComponent>();
    box_collider = BoxColliderComponent(width, height, glm::vec2(offset_x, offset_y));
}

/**
 * @brief get_box_collider of an entity.
 * @param entity The entity to get the box collider from.
 * @return A tuple containing the width and height of the box collider.
 */
std::tuple<int, int> get_box_collider(Entity entity)
{
    auto &box_collider = entity.get_component<BoxColliderComponent>();
    return {box_collider.width, box_collider.height};
}


#pragma endregion Collision and Physics Functions

#pragma region State Management Functions

/**
 * @brief Set the state of an entity.
 * @param entity The entity to set the state for.
 * @param state The state to set.
 */
void set_state(Entity entity, const int8_t state)
{
    auto &stateComponent = entity.get_component<StateComponent>();
    stateComponent.state = state;

    if (stateComponent.next_state == -1)
        stateComponent.next_state = state;
}

/**
 * @brief Get the state of an entity.
 * @param entity The entity to get the state from.
 * @return The state of the entity.
 */
int8_t get_state(Entity entity)
{
    auto &stateComponent = entity.get_component<StateComponent>();

    return stateComponent.state;
}

/**
 * @brief Set the next state of an entity.
 * @param entity The entity to set the next state for.
 * @param state The next state to set.
 */
void set_next_state(Entity entity, int8_t state)
{
    entity.get_component<StateComponent>().next_state = state;
}

/**
 * @brief Get the next state of an entity.
 * @param entity The entity to get the next state from.
 * @return The next state of the entity.
 */
int8_t get_next_state(Entity entity)
{
    return entity.get_component<StateComponent>().next_state;
}

# pragma endregion State Management Functions

#pragma region Stats and Player Functions

/**
 * @brief Increment the player velocity by a certain amount.
 * @param e The entity to increment the velocity for.
 * @param increment The amount to increment the velocity by.
 */
void increment_player_velocity(Entity e, int increment)
{
    auto &player_velocity = e.get_component<PlayerVelocity>();
    player_velocity.player_velocity += increment;
}

/**
 * @brief Get the player velocity.
 * @param e The entity to get the velocity from.
 * @return The player velocity.
 */
int get_player_velocity(Entity e)
{
    return e.get_component<PlayerVelocity>().player_velocity;
}

/**
 * @brief Get the health of an entity.
 * @param entity The entity to get the health from.
 */
int32_t get_health(Entity entity)
{
    auto &stats = entity.get_component<StatsComponent>();
    return stats.Health;
}

/**
 * @brief Set the health of an entity.
 * @param entity The entity to set the health for.
 * @param health The health to set.
 */
void set_health(Entity entity, int32_t health)
{
    entity.get_component<StatsComponent>().Health = health;
}

/**
 * @brief Get the damage of an entity.
 * @param entity The entity to get the damage from.
 */
int32_t get_damage(Entity entity)
{
    return entity.get_component<StatsComponent>().Damage;
}

/**
 * @brief Set the damage of an entity.
 * @param entity The entity to set the damage for.
 * @param damage The damage to set.
 */
int32_t get_points(Entity entity)
{
    return entity.get_component<StatsComponent>().Points;
}

/**
 * @brief Set the points of an entity.
 * @param entity The entity to set the points for.
 * @param points The points to set.
 */
void set_points(Entity entity, int32_t points)
{
    auto &stats = entity.get_component<StatsComponent>();
    auto difference = std::abs(stats.Points - points);
    stats.Points = points;
    stats.UltCounter += difference;
}

/**
 * @brief Get the ult counter of an entity.
 * @param entity The entity to get the ult counter from.
 */
int32_t get_ult_counter(Entity entity)
{
    return entity.get_component<StatsComponent>().UltCounter;
}

/**
 * @brief Set the ult counter of an entity.
 * @param entity The entity to set the ult counter for.
 * @param amount The amount to set the ult counter to.
 */
void set_ult_counter(Entity entity, int32_t amount)
{
    auto &stats = entity.get_component<StatsComponent>();
    stats.UltCounter = amount;
}

#pragma endregion Stats and Player Functions

#pragma region Rotation Functions
/**
 * @brief Set the rotation of an entity.
 * @param e The entity to set the rotation for.
 * @param angle The angle to set the rotation to.
 */
void set_rotation(Entity e, float angle)
{
    auto &transform = e.get_component<TransformComponent>();
    transform.rotation = angle;
}

/**
 * @brief Get the rotation of an entity.
 * @param e The entity to get the rotation from.
 * @return The rotation of the entity.
 */
float get_rotation(Entity e)
{
    return e.get_component<TransformComponent>().rotation;
}


#pragma endregion Rotation Functions

#pragma region Audio Functions

/**
 * @brief Play a sound effect.
 * @param sound_id The ID of the sound effect to play.
 */
void play_sound(const std::string &sound_id)
{
    Game::get_instance().audio_manager->play_sound_effect(sound_id);
}

/**
 * @brief Play a music track.
 * @param music_id The ID of the music track to play.
 */
void play_music(const std::string &music_id)
{
    Game::get_instance().audio_manager->play_music(music_id);
}

/**
 * @brief Stop all sounds and music.
 */
void stop_all_sounds()
{
    Game::get_instance().audio_manager->stop_all_sounds();
}

#pragma endregion Audio Functions

#pragma region Controller and Input Functions

/**
 * @brief Get the mouse position.
 * @return A tuple containing the x and y coordinates of the mouse.
 */
std::tuple<int, int> get_mouse_position()
{
    return Game::get_instance().controller_manager->get_mouse_position();
}

/**
 * @brief Check if a mouse button is pressed.
 * @param button The button to check.
 * @return True if the button is pressed, false otherwise.
 */
bool is_mouse_button_pressed(const std::string &button)
{
    return Game::get_instance().controller_manager->is_mouse_button_pressed(button);
}

/**
 * @brief Check if an action is activated.
 * @param action The action to check.
 * @return True if the action is activated, false otherwise.
 */
bool is_action_activated(const std::string &action)
{
    return Game::get_instance().controller_manager->is_key_pressed(action);
}

/**
 * @brief Activate an action.
 * @param action The action to activate.
 */
void activate_action(const std::string &action)
{
    Game::get_instance().controller_manager->update_key(action, true);
}

#pragma endregion Controller and Input Functions

#pragma region Scene Management Functions

/**
 * @brief Go to a scene.
 * @param scene_name The name of the scene to go to.
 */
void go_to_scene(const std::string &scene_name)
{
    Game::get_instance().scene_manager->set_next_scene(scene_name);
    Game::get_instance().scene_manager->stop_scene();
}

/**
 * @brief Reset the camera to the default position.
 */
void reset_camera()
{
    auto &camera = Game::get_instance().camera;
    camera.x = 0;
    camera.y = 0;
}

#pragma endregion Scene Management Functions

#pragma region Action and Cooldown Functions

/**
 * @brief Check if an entity can perform an action.
 * @param entity The entity to check.
 * @param action The action to check.
 * @return True if the entity can perform the action, false otherwise.
 */
bool can_perform_action(Entity entity, const std::string &action)
{
    if (!entity.has_component<CooldownsComponent>())
        return false;

    auto &cooldowns = entity.get_component<CooldownsComponent>();
    if (action == "") return cooldowns.CanPerformAction("");
    if (!cooldowns.CanPerformAction("") || !cooldowns.CanPerformAction(action))
        return false;

    return true;
}

/**
 * @brief Perform an action.
 * @param entity The entity to perform the action for.
 * @param action The action to perform.
 */
void perform_action(Entity entity, const std::string &action)
{
    if (!can_perform_action(entity, action))
        return;
    entity.get_component<CooldownsComponent>().PerformAction(action);
}

#pragma endregion Action and Cooldown Functions

#pragma region Parent-Child Entity Functions

/**
 * @brief Get the father entity of an entity.
 * @param entity The entity to get the father entity from.
 * @return The father entity of the entity.
 */
Entity get_father_entity(Entity entity)
{
    return entity.get_component<ChildComponent>().Father.value();
}

#pragma endregion Parent-Child Entity Functions

// animation related functions

// Audio related functions


// General entity related functions





// /**
//  * @brief Reset the bullet.
//  * @param e The bullet entity to reset.
//  */
// void reset_bullet(Entity e) {
//     // set velocity to 0
//     auto& rigid_body = e.get_component<RigidBodyComponent>();

//     rigid_body.velocity = {0, 0};

//     // get the player location from the game
//     auto& game = Game::get_instance();
//     auto [x, y] = game.player_location;

//     // set the bullet location to the player location
//     auto& transform = e.get_component<TransformComponent>();
//     transform.position = {static_cast<float>(x), static_cast<float>(y)};
// }

// /**
//  * @brief Update the player location.
//  * @param x The x coordinate of the player.
//  * @param y The y coordinate of the player.
//  */
// void update_player_location(int x, int y) {
//     Game::get_instance().player_location = {x, y};
// }






// Control related functions



// void increase_score(int score)
// {
//     Game::get_instance().player_score += score;
//     // print the score to the console
//     // std::cout << "Score: " <<  Game::get_instance().player_score << std::endl;
// }

// Movement, rotation and position related functions





// RigidBody related functions









// Scene related functions



// Sprite related functions














// stats related functions





#endif // LUA_BINDING_HPP