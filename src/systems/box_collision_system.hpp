#ifndef BOX_COLLLSIION_SYSTEM_HPP
#define BOX_COLLLSIION_SYSTEM_HPP

#include "../components/box_collider_component.hpp" // BoxColliderComponent
#include "../components/script_component.hpp" // ScriptComponent
#include "../components/transform_component.hpp" // TransformComponent
#include "../ECS/ECS.hpp" // System
#include "../event_manager/event_manager.hpp"
#include "../events/collision_event.hpp"

#include <iostream> // std::cout

/**
 * @brief The BoxCollisionSystem class is a class for managing box collisions.
 */
class BoxCollisionSystem : public System {
private:

    /**
     * @brief Check if there is a collision between two AABBs.
     * @param a_x The x position of the first AABB
     * @param a_y The y position of the first AABB
     * @param a_w The width of the first AABB
     * @param a_h The height of the first AABB
     * @param b_x The x position of the second AABB
     * @param b_y The y position of the second AABB
     * @param b_w The width of the second AABB
     * @param b_h The height of the second AABB
     * @return true if there is a collision, false otherwise
     */
    bool check_AABB_collision(float a_x, float a_y, float a_w, float a_h, float b_x, float b_y, float b_w, float b_h) {
        return(
            a_x < b_x + b_w &&
            a_x + a_w > b_x &&
            a_y < b_y + b_h &&
            a_y + a_h > b_y
        );
    }

public:

    /**
     * @brief Construct a new BoxCollisionSystem object
     */
    BoxCollisionSystem() {
        RequireComponent<BoxColliderComponent>();
        RequireComponent<TransformComponent>();
    }

    /**
     * @brief Update the box collision system
     * @param lua The Lua state
     */
    void update(const std::unique_ptr<EventManager> &eventManager, sol::state& lua){
         auto entities = get_entities();
        for(auto i = entities.begin(); i != entities.end(); i++) {
            Entity a = *i;
            const auto& a_collider = a.get_component<BoxColliderComponent>();
            const auto& a_transform = a.get_component<TransformComponent>();

            // loop through all the entities
            for(auto j =i; j != entities.end(); j++) {
                Entity b = *j;

                if(a==b) {
                    continue;
                }

                const auto& b_collider = b.get_component<BoxColliderComponent>();
                const auto& b_transform = b.get_component<TransformComponent>();
                
                // check if there is a collision
                bool there_is_collision = check_AABB_collision(
                    a_transform.position.x,
                    a_transform.position.y,
                    static_cast<float>(a_collider.width),
                    static_cast<float>(a_collider.height),
                    b_transform.position.x,
                    b_transform.position.y,
                    static_cast<float>(b_collider.width),
                    static_cast<float>(b_collider.height)
                );
                
                // check if there is a collision
                if(there_is_collision) {
                    eventManager->emit_event<CollisionEvent>(a, b);

                    if(a.has_component<ScriptComponent>()) {
                        const auto& script = a.get_component<ScriptComponent>();
                        if(script.on_collision != sol::nil) {
                            lua["this"] = a;
                            script.on_collision(b);
                        }

                    }

                    if(b.has_component<ScriptComponent>()) {
                        const auto& script = b.get_component<ScriptComponent>();
                        if(script.on_collision != sol::nil) {
                            lua["this"] = b;
                            script.on_collision(a);
                        }

                    }
                }
            }
        }
    }
};
#endif // BOX_COLLLSIION_SYSTEM_HPP