#ifndef CIRCLE_COLLISION_SYSTEM_HPP
#define CIRCLE_COLLISION_SYSTEM_HPP

#include <iostream>
#include <memory>

#include "../ECS/ECS.hpp"
#include "../components/transform_component.hpp"
#include "../components/circle_collider_component.hpp"
#include "../components/script_component.hpp"
#include "../components/tag_component.hpp"
#include "../event_manager/event_manager.hpp"
#include "../events/collision_event.hpp"

/**
 * @brief The CircleCollisionSystem class manages circle collisions.
 */
class CircleCollisionSystem : public System {
public:
    /**
     * @brief Construct a new CircleCollisionSystem object
     */
    CircleCollisionSystem() {
        RequireComponent<CircleColliderComponent>();
        RequireComponent<TransformComponent>();
    }

    /**
     * @brief Update collision detection for entities
     * @param event_manager Pointer to the event manager
     * @param lua Lua state for script execution
     */
    void update(std::unique_ptr<EventManager>& event_manager, sol::state& lua) {
        auto entities = get_entities();
        for(auto i = entities.begin(); i != entities.end(); i++) {
            Entity a = *i;
            auto a_collider = a.get_component<CircleColliderComponent>();
            auto a_transform = a.get_component<TransformComponent>();

            for(auto j = std::next(i); j != entities.end(); j++) {
                Entity b = *j;

                auto b_collider = b.get_component<CircleColliderComponent>();
                auto b_transform = b.get_component<TransformComponent>();

                // Use original position as center point
                glm::vec2 a_center_pos = glm::vec2(
                    a_transform.position.x,
                    a_transform.position.y
                );

                glm::vec2 b_center_pos = glm::vec2(
                    b_transform.position.x, 
                    b_transform.position.y
                );

                // Scale radius based on transform
                int a_radius = a_collider.radius * a_transform.scale.x;
                int b_radius = b_collider.radius * b_transform.scale.x;

                bool there_is_collision = check_circle_collision(a_radius, b_radius, a_center_pos, b_center_pos);

                // If there is a collision, emit event and trigger scripts
                if(there_is_collision) {
                    //event_manager->emit_event<CollisionEvent>(a, b);

                    // std::cout << "Circular collision detected between: " << std::endl;
                    // std::cout << "Entity A: " << a.get_component<TagComponent>().tag << std::endl;
                    // std::cout << "Entity B: " << b.get_component<TagComponent>().tag << std::endl;

                    trigger_collision_script(a, b, lua);
                    trigger_collision_script(b, a, lua);
                }
            }
        }
    }

private:
    /**
     * @brief Check if there is a collision between two circles.
     * @param a_radius The radius of the first circle
     * @param b_radius The radius of the second circle
     * @param a_pos The position of the first circle
     * @param b_pos The position of the second circle
     * @return true if there is a collision, false otherwise
     */
    bool check_circle_collision(int a_radius, int b_radius, glm::vec2 a_pos, glm::vec2 b_pos) {
        glm::vec2 dif = a_pos - b_pos;
        
        // Calculate squared distance between centers
        float distance_squared = (dif.x * dif.x) + (dif.y * dif.y);
        
        // Calculate the sum of radii
        float radii_sum = a_radius + b_radius;
        
        // Check if the squared distance is less than or equal to the squared sum of radii
        return distance_squared <= (radii_sum * radii_sum);
    }

    /**
     * @brief Trigger collision script for an entity
     * @param entity Entity to check for script component
     * @param other_entity Colliding entity
     * @param lua Lua state for script execution
     */
    void trigger_collision_script(Entity& entity, Entity& other_entity, sol::state& lua) {
        if(entity.has_component<ScriptComponent>()) {
            const auto& script = entity.get_component<ScriptComponent>();
            if(script.on_collision != sol::nil) {
                lua["this"] = entity;
                script.on_collision(other_entity);
            }
        }
    }
};

#endif // CIRCLE_COLLISION_SYSTEM_HPP