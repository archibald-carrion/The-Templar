//
// Created by joe on 12/3/24.
//

#ifndef ATTACK_SYSTEM_HPP
#define ATTACK_SYSTEM_HPP

#include <sol/sol.hpp>

#include "../ECS/ECS.hpp"
#include "../components/cooldown_component.hpp"
#include "../components/transform_component.hpp"
#include "../components/sprite_component.hpp"
#include "../components/RigidBodyComponent.hpp"
#include "../event_manager/event_manager.hpp"
#include "../events/click_event.hpp"
#include "../components/script_component.hpp"

class AttackSystem : public System {
public:
    AttackSystem() {
        this->RequireComponent<TransformComponent>();
        this->RequireComponent<SpriteComponent>();
        this->RequireComponent<RigidBodyComponent>();
        this->RequireComponent<CooldownsComponent>();
        this->RequireComponent<ScriptComponent>();
    }

    void update(EventManager& eventManager) {
        eventManager.subscribe_to_event<ClickEvent, AttackSystem>(
          this
          , &AttackSystem::attack);
    }

    void attack(ClickEvent& e) {
        for (auto& entity : this->get_entities()) {
            auto& cooldowns = entity.get_component<CooldownsComponent>();
            if (!cooldowns.CanPerformAction("")) continue;

            ScriptComponent& script = entity.get_component<ScriptComponent>();
            if (script.perform == sol::lua_nil) continue;

            bool clickRegistered = false;

            switch(e.button_code) {
                case SDL_BUTTON_LEFT: // attack forward
                    clickRegistered = true;
					script.perform();
                    break;
                case SDL_BUTTON_RIGHT: // another attack?
                    //clickRegistered = true;
                    break;
                default:
                    break;
            }

            if (clickRegistered) {
                cooldowns.PerformAction("");
            }
        }
    }
};

#endif //ATTACK_SYSTEM_HPP
