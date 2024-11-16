#ifndef UI_SYSTEM_HPP
#define UI_SYSTEM_HPP

#include <SDL2/SDL.h> // SDL library for window creation and rendering
#include <memory> // std::unique_ptr
#include <iostream> // std::cout
#include <string> // std::string
#include "../ECS/ECS.hpp" // System
#include "../components/clickable_component.hpp" // ClickableComponent
#include "../components/text_component.hpp" // TextComponent
#include "../components/transform_component.hpp" // TransformComponent
#include "../components/script_component.hpp" // ScriptComponent
#include "../event_manager/event_manager.hpp" // EventManager
#include "../events/click_event.hpp" // ClickEvent

/**
 * @brief The UISystem class is a class for managing UI elements.
 */
class UISystem : public System {
public:

    /**
     * @brief Construct a new UISystem object
     */
    UISystem() {
        RequireComponent<ClickableComponent>();
        RequireComponent<TransformComponent>();
        RequireComponent<TextComponent>();
    }

    /**
     * @brief Update the UI system
     * @param event_manager The event manager
     */
    void suscribe_to_click_event(std::unique_ptr<EventManager>& event_manager) {
        event_manager->subscribe_to_event<ClickEvent, UISystem>(this, &UISystem::on_click);
    }

    /**
     * @brief Update the UI system
     * @param e The click event
     */
    void on_click(ClickEvent& e) {
        for(auto entity : get_entities()) {
            const auto& transform = entity.get_component<TransformComponent>();
            const auto& text = entity.get_component<TextComponent>();

            bool is_click_inside =  transform.position.x < e.position_x &&
                                    e.position_x < transform.position.x + text.width &&
                                    transform.position.y < e.position_y &&
                                    e.position_y < transform.position.y + text.height;
            
            // check if the click is inside the text and call the on_click function
            if (is_click_inside) {
                if(entity.has_component<ScriptComponent>()) {
                    const auto& script = entity.get_component<ScriptComponent>();
                    if(script.on_click != sol::lua_nil) {
                        script.on_click();
                    }
                }
            }
        }
    }
};


#endif // UI_SYSTEM_HPP