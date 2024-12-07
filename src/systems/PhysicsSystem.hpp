#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include "../components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief The PhysicsSystem class
 * The PhysicsSystem class is a class for managing physics.
 */
class PhysicsSystem : public System {
public:

    /**
     * @brief Construct a new Physics System object
     */
    PhysicsSystem() {
        RequireComponent<RigidBodyComponent>();
    }

    /**
     * @brief Update the physics system
     */
    void update() {
        for (auto entity : get_entities()) {
            auto& rigidbody = entity.get_component<RigidBodyComponent>();

            // apply gravity
            if (rigidbody.is_dynamic) {
                rigidbody.sum_forces += glm::vec2(0.0f, 9.8 * rigidbody.mass * 64);
            }
        }
    }
};

#endif // PHYSICSSYSTEM_HPP