#ifndef CIRCLE_COLLISION_SYSTEM_HPP
#define CIRCLE_COLLISION_SYSTEM_HPP

/// @file circle_collision_system.hpp, no longer used in the project, collision is currently handled using AABB collision

#include <iostream> // std::cout
#include <memory> // std::unique_ptr

#include "../ECS/ECS.hpp" // System
#include "../components/transform_component.hpp" // TransformComponent
#include "../components/circle_collider_component.hpp" // CircleColliderComponent
#include "../event_manager/event_manager.hpp" // EventManager
#include "../events/collision_event.hpp" // CollisionEvent

/**
 * @brief The CircleCollisionSystem class is a class for managing circle collisions.
 */
class CircleCollisionSystem : public System {
public:

    /**
     * @brief Construct a new CircleCollisionSystem object
     */
    CircleCollisionSystem(/* args */) {
        RequireComponent<CircleColliderComponent>();
        RequireComponent<TransformComponent>();
    }

    /**
     * @brief Destroy the CircleCollisionSystem object
     */
    void update(std::unique_ptr<EventManager>& event_manager) {
        auto entities = get_entities();
        for(auto i = entities.begin(); i != entities.end(); i++) {
            Entity a = *i;
            auto a_collider = a.get_component<CircleColliderComponent>();
            auto a_transform = a.get_component<TransformComponent>();

            for(auto j =i; j != entities.end(); j++) {
                Entity b = *j;

                if(a==b) {
                    continue;
                }

                auto b_collider = b.get_component<CircleColliderComponent>();
                auto b_transform = b.get_component<TransformComponent>();

                glm::vec2 a_center_pos = glm::vec2(
                    a_transform.position.x - (a_collider.width/2)* a_transform.scale.x,
                    a_transform.position.y - (a_collider.height/2)* a_transform.scale.y
                );

                glm::vec2 b_center_pos = glm::vec2(
                    b_transform.position.x - (b_collider.width/2)* b_transform.scale.x, 
                    b_transform.position.y - (b_collider.height/2)* b_transform.scale.y
                );

                int a_radius = a_collider.radius*a_transform.scale.x;
                int b_radius = b_collider.radius*b_transform.scale.x;

                bool there_is_collision = check_circle_collision(a_radius, b_radius, a_center_pos, b_center_pos);

                // if there is a collision emit a collision event
                if(there_is_collision) {
                    event_manager->emit_event<CollisionEvent>(a, b);
                }
            }

        }
    }

    /**
     * @brief Check if there is a collision between two circles.
     * @param a_radius The radius of the first circle
     * @param b_radius The radius of the second circle
     * @param a_pos The position of the first circle
     * @param b_pos The position of the second circle
     * @return true if there is a collision, false otherwise
     */
    bool  check_circle_collision(int a_radius, int b_radius, glm::vec2 a_pos, glm::vec2 b_pos) {
        glm::vec2 dif = a_pos - b_pos;
        double lenght =glm::sqrt((dif.x*dif.x)+(dif.y*dif.y));

        bool is_colliding = (a_radius+b_radius) >= lenght;

        return is_colliding;

    }

};


#endif // CIRCLE_COLLISION_SYSTEM_HPP