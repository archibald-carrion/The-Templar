#ifndef ENEMY_COLLISION_SYSTEM_HPP
#define ENEMY_COLLISION_SYSTEM_HPP

#include <sol/sol.hpp>

#include "../ECS/ECS.hpp"
#include "../components/enemy_box_collider_component.hpp"
#include "../components/script_component.hpp"
#include "../components/transform_component.hpp"
#include "../components/tag_component.hpp"
#include "../event_manager/event_manager.hpp"

class EnemyCollisionSystem : public System {
    struct Info {
        float X;
        float Y;
        int32_t Width;
        int32_t Height;
    };

public:
    EnemyCollisionSystem() {
        this->RequireComponent<EnemyColliderComponent>();
        RequireComponent<TransformComponent>();
        RequireComponent<TagComponent>();
    }

    void update(const std::unique_ptr<EventManager> &eventManager, sol::state& lua) {
        auto entities = get_entities();

        for (auto i = entities.begin(); i != entities.end(); ++i) {
            Entity a = *i;

            const auto& aCollider = a.get_component<EnemyColliderComponent>();
            const auto& aTransform = a.get_component<TransformComponent>();

            for (auto j = i + 1; j != entities.end(); ++j) {
                Entity b = *j;
                const auto& bCollider = b.get_component<EnemyColliderComponent>();
                const auto& bTransform = b.get_component<TransformComponent>();

                const bool there_is_collision = EnemyCollisionSystem::checkAABBCollision(
                    { aTransform.position.x, aTransform.position.y, 
                      aCollider.width, aCollider.height },
                    { bTransform.position.x, bTransform.position.y, 
                      bCollider.width, bCollider.height }
                );

                // check if there is a collision
                if(there_is_collision) {
                    //eventManager->emit_event<CollisionEvent>(a, b);

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

    static bool checkAABBCollision(const Info& a, const Info& b) {
        return
            a.X < b.X + b.Width &&
            a.X + a.Width > b.X &&
            a.Y < b.Y + b.Height &&
            a.Y + a.Height > b.Y
        ;
    }
};

#endif //ENEMY_COLLISION_SYSTEM_HPP