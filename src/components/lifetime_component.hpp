//
// Created by joe on 12/4/24.
//

#ifndef LIFETIME_COMPONENT_HPP
#define LIFETIME_COMPONENT_HPP

#include <variant>
#include <functional>

#include "../ECS/ECS.hpp"

/**
 * @brief Interface for components to erase
 *
 */
struct IComponentToErase {
    virtual ~IComponentToErase() = default;
    virtual void RemoveComponent(Entity& entity) = 0;
};

/**
 * @brief Component to erase a component
 *
 * @tparam TComponent
 */
template<typename TComponent>
struct ComponentToErase final : public IComponentToErase {
    void RemoveComponent(Entity& entity) override {
        entity.remove_component<TComponent>();
    }
};

/**
 * @brief Filler for when there is nothing to do
 *
 */
struct Nothing {
};

/**
 * @brief Component for the lifetime of an entity
 *
 */
struct LifetimeComponent {
    float TicksAlive = 0;

    std::variant<std::shared_ptr<IComponentToErase>
        , std::function<void(const Entity&)>
        , Nothing> Action
    = Nothing();

    explicit LifetimeComponent(const float ticksAlive = 0) : TicksAlive(ticksAlive) {};

    LifetimeComponent& operator -= (const float amount) {
        TicksAlive -= amount;
        return *this;
    }

    [[nodiscard]] bool IsAlive() const {
        return TicksAlive >= 0;
    }
};

#endif //LIFETIME_COMPONENT_HPP
