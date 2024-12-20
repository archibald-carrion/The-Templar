#ifndef SCRIPT_SYSTEM_HPP
#define SCRIPT_SYSTEM_HPP

#include <sol/sol.hpp>                        // Lua scripting
#include <memory>                             // std::unique_ptr
#include "../binding/lua_binding.hpp"         // Lua bindings
#include "../components/script_component.hpp" // ScriptComponent
#include "../ECS/ECS.hpp"                     // System

/**
 * @brief Script System class
 * The ScriptSystem class is a class for managing scripts.
 */
class ScriptSystem : public System {
public:
    /**
     * @brief Construct a new Script System object
     */
    ScriptSystem() {
        RequireComponent<ScriptComponent>();
    }

    /**
     * @brief Create a lua binding object
     * @param lua sol lua state
     */
    void create_lua_binding(sol::state& lua) {
        // Classes
        lua.new_usertype<Entity>("entity");

        // Controller and Input Functions
        lua.set_function("is_action_activated", is_action_activated);
        lua.set_function("is_mouse_button_pressed", is_mouse_button_pressed);
        lua.set_function("get_mouse_position", get_mouse_position);

        // Rigid Body and Movement Functions
        lua.set_function("set_velocity", set_velocity);
        lua.set_function("get_velocity", get_velocity);
        lua.set_function("get_buffered_velocity", get_buffered_velocity);
        lua.set_function("set_rotation", set_rotation);
        lua.set_function("get_rotation", get_rotation);
        lua.set_function("set_position", set_position);
        lua.set_function("get_position", get_position);
        lua.set_function("get_size", get_size);
        lua.set_function("add_force", add_force);

        // Animation and Sprite Functions
        lua.set_function("change_animation", change_animation);
        lua.set_function("get_animation_frame", get_animation_frame);
        lua.set_function("flip_sprite", flip_sprite);
        lua.set_function("looking_right", looking_right);

        // Entity Management Functions
        lua.set_function("get_tag", get_tag);
        lua.set_function("get_class", get_class);
        lua.set_function("kill_entity", kill_entity);
        lua.set_function("increment_player_velocity", increment_player_velocity);
        lua.set_function("get_player_velocity", get_player_velocity);

        // Scene Management Functions
        lua.set_function("go_to_scene", go_to_scene);
        lua.set_function("reset_camera", reset_camera);

        // Collision and Physics Functions
        lua.set_function("top_collision", top_collision);
        lua.set_function("left_collision", left_collision);
        lua.set_function("bottom_collision", bottom_collision);
        lua.set_function("right_collision", right_collision);
        lua.set_function("set_box_collider", set_box_collider);
        lua.set_function("get_box_collider", get_box_collider);

        // Audio Functions
        lua.set_function("play_sound", play_sound);
        lua.set_function("play_music", play_music);
        lua.set_function("stop_all_sounds", stop_all_sounds);

        // State Management Functions
        lua.set_function("get_state", get_state);
        lua.set_function("set_state", set_state);
        lua.set_function("set_next_state", set_next_state);
        lua.set_function("get_next_state", get_next_state);

        // Action and Cooldown Functions
        lua.set_function("can_perform_action", can_perform_action);
        lua.set_function("perform_action", perform_action);

        // Projectile Functions
        lua.set_function("create_projectile", create_projectile);
        lua.set_function("create_projectile_with_animation", create_projectile_with_animation);
        lua.set_function("shoot_fireball", shoot_fireball);

        // Stats and Player Functions
        lua.set_function("get_health", get_health);
        lua.set_function("set_health", set_health);
        lua.set_function("get_damage", get_damage);
        lua.set_function("get_points", get_points);
        lua.set_function("set_points", set_points);
        lua.set_function("get_father", get_father_entity);
        lua.set_function("get_ult", get_ult_counter);
        lua.set_function("set_ult", set_ult_counter);
    }

    /**
     * @brief Update the script system
     * @param lua sol lua state
     */
    void update(sol::state& lua) {
        for (auto& entity : get_entities()) {
            const auto& script = entity.get_component<ScriptComponent>();

            if (script.update != sol::lua_nil) {
                lua["this"] = entity;
                script.update();
            }
        }
    }

    /**
     * @brief init function that calls the on_init function from the script component
     * @param lua sol lua state
     */
    void init_from_script(sol::state& lua) {
        // loop through all entities and call the on_init function
        for (auto& entity : get_entities()) {
            const auto& script = entity.get_component<ScriptComponent>();
            // check if the on_init function exists
            if (script.on_init != sol::lua_nil) {
                lua["this"] = entity;
                script.on_init();
            }
        }
    }
};

#endif // SCRIPT_SYSTEM_HPP