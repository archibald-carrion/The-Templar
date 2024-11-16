#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include <sol/sol.hpp> // Lua scripting

/**
 * @struct ScriptComponent
 * @brief The ScriptComponent struct represents a script component for an entity.
 */
struct ScriptComponent {
    sol::function update; // update function
    sol::function on_collision; // on collision function
    sol::function on_click; // on click function
    sol::function on_init; // on init function

    /**
     * @brief Construct a new Script Component object
     * @param on_collision The on collision function
     * @param update The update function
     * @param on_click The on click function
     * @param on_init The on init function
     */
    ScriptComponent(sol::function  on_collision = sol::lua_nil, sol::function update= sol::lua_nil, sol::function on_click= sol::lua_nil, sol::function on_init= sol::lua_nil) {
        this->on_collision = on_collision;
        this->update = update;
        this->on_click = on_click;
        this->on_init = on_init;
    }
};


#endif // SCRIPT_COMPONENT_HPP