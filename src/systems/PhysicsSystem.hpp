#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include "../components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"

class PhysicsSystem : public System {
public:
    PhysicsSystem() {
        RequireComponent<RigidBodyComponent>();
    }

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