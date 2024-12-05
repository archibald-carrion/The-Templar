#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../ECS/ECS.hpp" // System
#include "../components/RigidBodyComponent.hpp" // RigidBodyComponent
#include "../components/transform_component.hpp" // TransformComponent
#include "../components/tag_component.hpp"

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

            if (entity.has_component<SpriteComponent>() && entity.has_component<BoxColliderComponent>()) {
                auto& sprite = entity.get_component<SpriteComponent>();
                auto& collider = entity.get_component<BoxColliderComponent>();

                transform.sprite_h_offset = sprite.width / 2 * transform.scale.x - collider.width / 2;
            }

            transform.previous_position = transform.position;

            if (rigid_body.is_dynamic) {
                rigid_body.acceleration = rigid_body.sum_forces * rigid_body.inverse_mass;
                rigid_body.velocity += rigid_body.acceleration * static_cast<float>(dt);
                transform.position += rigid_body.velocity * static_cast<float>(dt);
                rigid_body.sum_forces = glm::vec2(0, 0);
            }

            if (rigid_body.father) {
                std::swap(transform.position, transform.movement_offset.value());
            }

            if (rigid_body.default_movement) {
                transform.position.x += rigid_body.velocity.x * dt;
                transform.position.y += rigid_body.velocity.y * dt;
                rigid_body.bufferVelocity();
            }

            if (rigid_body.father) {
                auto& father_transform = rigid_body.father->get_component<TransformComponent>();
                transform.movement_offset.value() = transform.position + father_transform.position;
                std::swap(transform.position, transform.movement_offset.value());
            }
        }
    }
};

#endif // MOVEMENTSYSTEM_HPP