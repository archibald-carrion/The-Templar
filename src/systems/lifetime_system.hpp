//
// Created by joe on 12/4/24.
//

#ifndef LIFETIME_SYSTEM_HPP
#define LIFETIME_SYSTEM_HPP

#include "../ECS/system.hpp"
#include "../components/lifetime_component.hpp"

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

inline void manageLifetime(LifetimeComponent& lifetimeComponent, Entity& entity);

class LifetimeSystem : public System {
public:
    LifetimeSystem() {
        this->RequireComponent<LifetimeComponent>();
    }

    void update(const float deltaTime) {
        for (auto& entity : this->get_entities()) {
            auto& lifetimeComponent = entity.get_component<LifetimeComponent>();

            lifetimeComponent -= deltaTime;

            if (!lifetimeComponent.IsAlive()) {
                manageLifetime(lifetimeComponent, entity);
            }
        }
    }
};


inline void manageLifetime(LifetimeComponent& lifetimeComponent, Entity& entity) {
    std::visit( overloaded {
        [&](Nothing) { entity.kill(); },
        [&](const std::shared_ptr<IComponentToErase>& componentToErase) {
            if (componentToErase) componentToErase->RemoveComponent(entity);
        },
        [&](const std::function<void(const Entity&)>& action) { action(entity); }
    }, lifetimeComponent.Action);
}

#endif //LIFETIME_SYSTEM_HPP
