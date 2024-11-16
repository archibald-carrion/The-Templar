#ifndef DAMAGE_SYSTEM_HPP
#define DAMAGE_SYSTEM_HPP

/// @file damage_system.hpp, no longer used in the project, collision is currently handled in the Lua scripts

#include <memory> // std::unique_ptr
#include <iostream> // std::cout
#include "../ECS/ECS.hpp" // System
#include "../components/circle_collider_component.hpp" // CircleColliderComponent
#include "../event_manager/event_manager.hpp" // EventManager
#include "../events/collision_event.hpp" // CollisionEvent

/**
 * @brief The DamageSystem class is a class for managing damage.
 */
class DamageSystem : public System {
public:

    /**
     * @brief Construct a new DamageSystem object
     */
    DamageSystem() {
        RequireComponent<CircleColliderComponent>();
    }

    /**
     * @brief Destroy the DamageSystem object
     */
    void subscribe_to_collision_event(std::unique_ptr<EventManager>& event_manager) {
        event_manager->subscribe_to_event<CollisionEvent, DamageSystem>(this, &DamageSystem::on_collision);
    }

    /**
     * @brief Update the damage system
     */
    void on_collision(CollisionEvent& e) {
        // std::cout << "[DAMAGESYSTEM] collision between " << e.a.get_id() << " and " << e.b.get_id() << std::endl;
        e.a.kill();
        e.b.kill();
    }

};


#endif // DAMAGE_SYSTEM_HPP