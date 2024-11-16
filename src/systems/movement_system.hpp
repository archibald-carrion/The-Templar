#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../ECS/ECS.hpp" // System
#include "../components/RigidBodyComponent.hpp" // RigidBodyComponent
#include "../components/transform_component.hpp" // TransformComponent

/**
 * @brief The MovementSystem class is a class for managing movement.
 */
class MovementSystem : public System {
public:

    /**
     * @brief Construct a new MovementSystem object
     */
    MovementSystem() {
        RequireComponent<RigidBodyComponent>();
        RequireComponent<TransformComponent>();
    }

    /**
     * @brief update the movement system
     * @param dt The delta time
     */
    void update(double dt) {
        // loop through all the entities
        for(auto entity: get_entities()) {
            auto& rigid_body = entity.get_component<RigidBodyComponent>();
            auto& transform = entity.get_component<TransformComponent>();

            transform.previous_position = transform.position;

            if(rigid_body.is_dynamic) {
                rigid_body.acceleration = rigid_body.sum_forces * rigid_body.inverse_mass;
                rigid_body.velocity += rigid_body.acceleration * static_cast<float>(dt);
                transform.position += rigid_body.velocity * static_cast<float>(dt);
                rigid_body.sum_forces = glm::vec2(0, 0);
            } else {
                transform.position.x += rigid_body.velocity.x * dt;
                transform.position.y += rigid_body.velocity.y * dt;
            }

        }
    }

};

#endif // MOVEMENTSYSTEM_HPP