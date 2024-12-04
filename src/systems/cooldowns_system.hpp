//
// Created by joe on 12/3/24.
//

#ifndef COOLDOWNS_SYSTEM_HPP
#define COOLDOWNS_SYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../components/cooldown_component.hpp"

class CooldownsSystem : public System {
public:
    CooldownsSystem() {
        this->RequireComponent<CooldownsComponent>();
    }

    void update(const double deltaTime) {
        for (auto& entity : this->get_entities()) {
            auto&[global, playerActions, lastPerformed, buffer] =
                entity.get_component<CooldownsComponent>();

            for (auto& [name,action] : playerActions) {
                action.Counter += deltaTime;
                if ((action.Counter < 0 || action.Counter >= action.TimeLimit) && lastPerformed == name) {
                    lastPerformed = "";
                }
            }

            global.Counter += deltaTime;

            if ((global.Counter < 0 || global.Counter >= global.TimeLimit) && !lastPerformed.empty()) {
                lastPerformed = "";
            }
        }
    }
};

#endif //COOLDOWNS_SYSTEM_HPP
