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
    sol::function on_damage;
    sol::function on_perform;

    /**
     * @brief Construct a new Script Component object
     * @param on_collision The on collision function
     * @param update The update function
     * @param on_click The on click function
     * @param on_init The on init function
     */
    explicit ScriptComponent(
        const sol::function& on_collision = sol::lua_nil
        , const sol::function& update= sol::lua_nil
        , const sol::function& on_click= sol::lua_nil
        , const sol::function& on_init= sol::lua_nil
        , const sol::function& on_damage = sol::lua_nil
        , const sol::function& on_perform = sol::lua_nil) :
    update(std::move(update))
    , on_collision(std::move(on_collision))
    , on_click(std::move(on_click))
    , on_init(std::move(on_init))
    , on_damage(std::move(on_damage))
    , on_perform(std::move(on_perform)){
    }
};


#endif // SCRIPT_COMPONENT_HPP