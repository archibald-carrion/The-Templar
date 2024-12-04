//
// Created by joe on 12/3/24.
//

#ifndef DAMAGE_COLLISION_SYSTEM_HPP
#define DAMAGE_COLLISION_SYSTEM_HPP

#include <sol/sol.hpp>

#include "../ECS/ECS.hpp"
#include "../components/damage_collider_component.hpp"
#include "../components/script_component.hpp"
#include "../components/transform_component.hpp"
#include "../components/tag_component.hpp"
#include "../event_manager/event_manager.hpp"

class DamageCollisionSystem : public System {
    struct Info {
        float X;
        float Y;
        int32_t Width;
        int32_t Height;
    };

public:
    DamageCollisionSystem() {
        this->RequireComponent<DamageColliderComponent>();
        RequireComponent<TransformComponent>();
        RequireComponent<TagComponent>();
    }

    void update(EventManager& eventManager, sol::state& lua) {
        auto entities = get_entities();

        for (auto i = entities.begin(); i != entities.end(); ++i) {
            Entity a = *i;

            const auto& aCollider = a.get_component<DamageColliderComponent>();
            const auto& aTransform = a.get_component<TransformComponent>();

            for (auto j = i + 1; j != entities.end(); ++j) {
                Entity b = *j;
                const auto& bCollider = b.get_component<DamageColliderComponent>();
                const auto& bTransform = b.get_component<TransformComponent>();

                const bool collision = DamageCollisionSystem::checkAABBCollision(
                    { aTransform.position.x, aTransform.position.y
                        , aCollider.Width, aCollider.Height },
                    { bTransform.position.x, bTransform.position.y
                        , bCollider.Width, bCollider.Height }
                );

                if (!collision) {
                    continue;
                }

                if (a.has_component<ScriptComponent>()) {
                    const auto& script = a.get_component<ScriptComponent>();
                    if (script.on_damage != sol::nil) {
                        lua["this"] = a;
                        (void) script.on_damage(b);
                    }
                }

                if (b.has_component<ScriptComponent>()) {
                    const auto& script = b.get_component<ScriptComponent>();
                    if (script.on_damage != sol::nil) {
                        lua["this"] = b;
                        (void) script.on_damage(a);
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

#endif //DAMAGE_COLLISION_SYSTEM_HPP
