#ifndef OVERLAPSYSTEM_HPP
#define OVERLAPSYSTEM_HPP

#include <memory>

#include "../components/box_collider_component.hpp"
#include "../components/RigidBodyComponent.hpp"
#include "../components/transform_component.hpp"
#include "../ECS/ECS.hpp"
#include "../event_manager/event_manager.hpp"
#include "../events/collision_event.hpp"

enum Direction
{
  TOP,
  BOTTOM,
  LEFT,
  RIGHT
};

/**
 * @brief The OverlapSystem class
 * The OverlapSystem class is a class for managing overlap collisions.
 */
class OverlapSystem : public System {

    /**
     * @brief Check if two entities are colliding.
     * @param a The first entity.
     * @param b The second entity.
     * @param dir The direction of the collision.
     * @return True if the entities are colliding, false otherwise.
     */
    bool check_collision(Entity a, Entity b, Direction dir) {
       auto &aCollider = a.get_component<BoxColliderComponent>();
        auto &bCollider = b.get_component<BoxColliderComponent>();
        auto &aTransform = a.get_component<TransformComponent>();
        auto &bTransform = b.get_component<TransformComponent>();

        float aX = aTransform.previous_position.x;
        float aY = aTransform.previous_position.y;
        float aW = static_cast<float>(aCollider.width);
        float aH = static_cast<float>(aCollider.height);

        float bX = bTransform.previous_position.x;
        float bY = bTransform.previous_position.y;
        float bW = static_cast<float>(bCollider.width);
        float bH = static_cast<float>(bCollider.height);

        if (Direction::TOP == dir)
            return (
                aX < bX + bW &&
                aX + aW > bX &&
                aY > bY //
            );

        if (Direction::BOTTOM == dir)
            return (
                aX < bX + bW &&
                aX + aW > bX &&
                aY < bY //
            );

        if (Direction::LEFT == dir)
            return (
                aY < bY + bH &&
                aY + aH > bY &&
                aX > bX //
            );

        if (Direction::RIGHT == dir)
            return (
                aY < bY + bH &&
                aY + aH > bY &&
                aX < bX //
            );

        return false;
    }

    /**
     * @brief Avoid overlap between two entities.
     * @param a The first entity.
     * @param b The second entity.
     */
    void avoid_overlap(Entity a, Entity b) {
        auto &aCollider = a.get_component<BoxColliderComponent>();
        auto &aTransform = a.get_component<TransformComponent>();

        auto &bCollider = b.get_component<BoxColliderComponent>();
        auto &bTransform = b.get_component<TransformComponent>();
        auto &bRigidBody = b.get_component<RigidBodyComponent>();

        if (check_collision(a, b, Direction::TOP))
        {
        bTransform.position = glm::vec2(bTransform.position.x, aTransform.position.y - bCollider.height);
        bRigidBody.velocity = glm::vec2(bRigidBody.velocity.x, 0.0f);
        }
        if (check_collision(a, b, Direction::BOTTOM))
        {
        bTransform.position = glm::vec2(bTransform.position.x, aTransform.position.y + aCollider.height);
        bRigidBody.velocity = glm::vec2(bRigidBody.velocity.x, 0.0f);
        }

        if (check_collision(a, b, Direction::LEFT))
        {
        bTransform.position = glm::vec2(aTransform.position.x - bCollider.width, bTransform.position.y);
        bRigidBody.velocity = glm::vec2(0.0f, bRigidBody.velocity.y);
        }
        if (check_collision(a, b, Direction::RIGHT))
        {
        bTransform.position = glm::vec2(aTransform.position.x + aCollider.width, bTransform.position.y);
        bRigidBody.velocity = glm::vec2(0.0f, bRigidBody.velocity.y);
        }
    }

public:
    /**
     * @brief Construct a new OverlapSystem object
     */
    OverlapSystem() {
        RequireComponent<BoxColliderComponent>();
        RequireComponent<RigidBodyComponent>();
        RequireComponent<TransformComponent>();
        RequireComponent<TagComponent>();
    }

    /**
     * @brief Update the overlap system
     * @param event_manager The event manager
     */
    void SubscribeToCollisionEvent(const std::unique_ptr<EventManager>& event_manager) {
        event_manager->subscribe_to_event<CollisionEvent, OverlapSystem>(this, &OverlapSystem::OnCollisionEvent);
    }

    /**
     * @brief Update the overlap system
     * @param event_manager The event manager
     */
    void OnCollisionEvent(CollisionEvent& e) {
        auto& a_rigidbody = e.a.get_component<RigidBodyComponent>();
        auto& b_rigidbody = e.b.get_component<RigidBodyComponent>();

        if (a_rigidbody.is_solid && b_rigidbody.is_solid) {
            if(a_rigidbody.mass >= b_rigidbody.mass) {
                avoid_overlap(e.a, e.b);
            } else {
                avoid_overlap(e.b, e.a);
            }
       }
   }
};
#endif