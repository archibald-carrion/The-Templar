#ifndef SCRIPT_SYSTEM_HPP
#define SCRIPT_SYSTEM_HPP

#include <sol/sol.hpp> // Lua scripting
#include <memory> // std::unique_ptr
#include "../binding/lua_binding.hpp" // Lua bindings   
#include "../components/script_component.hpp" // ScriptComponent
#include "../ECS/ECS.hpp" // System

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
        // classes
        lua.new_usertype<Entity>("entity");

        // key and mouse related functions
        lua.set_function("is_action_activated", is_action_activated);
        lua.set_function("is_mouse_button_pressed", is_mouse_button_pressed);
        lua.set_function("get_mouse_position", get_mouse_position);

        // movement, rotation and position related functions 
        lua.set_function("set_velocity", set_velocity);
        lua.set_function("get_velocity", get_velocity);
        lua.set_function("set_rotation", set_rotation);
        lua.set_function("get_rotation", get_rotation);
        lua.set_function("set_position", set_position);
        lua.set_function("get_position", get_position);
        lua.set_function("get_size", get_size);

        lua.set_function("add_force", add_force);
        lua.set_function("flip_sprite", flip_sprite);
        lua.set_function("change_animation", change_animation);


        // general entity related functions
        lua.set_function("get_tag", get_tag);
        // lua.set_function("reset_bullet", reset_bullet);
        // lua.set_function("update_player_location", update_player_location);
        lua.set_function("kill_entity", kill_entity);
        lua.set_function("increment_player_velocity", increment_player_velocity);
        lua.set_function("get_player_velocity", get_player_velocity);
        lua.set_function("increase_score", increase_score);
        //lua.set_function("shoot_bullet", shoot_bullet);

        // scene related functions
        lua.set_function("go_to_scene", go_to_scene);

        // collision related functions
        lua.set_function("top_collision", top_collision);
        lua.set_function("left_collision", left_collision);
        lua.set_function("bottom_collision", bottom_collision);
        lua.set_function("right_collision", right_collision);

        // sound and music related functions
        lua.set_function("play_sound", play_sound);
        lua.set_function("play_music", play_music);
        lua.set_function("stop_all_sounds", stop_all_sounds);
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