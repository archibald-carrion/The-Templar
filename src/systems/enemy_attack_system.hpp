//
// Created by joe on 12/5/24.
//

#ifndef ENEMY_ATTACK_SYSTEM_HPP
#define ENEMY_ATTACK_SYSTEM_HPP

#include <sol/sol.hpp>

#include "../ECS/ECS.hpp"

#include "../components/script_component.hpp"
#include "../components/cooldown_component.hpp"
#include "../components/attack_cycle_component.hpp"
#include "../components/damage_collider_component.hpp"

#include "../utils/utilities.hpp"

class EnemyAttackSystem : public System {
public:
    EnemyAttackSystem () {
        this->RequireComponent<ScriptComponent>();
        this->RequireComponent<CooldownsComponent>();
        this->RequireComponent<AttackCycleComponent>();
        this->RequireComponent<DamageColliderComponent>();
        this->RequireComponent<TransformComponent>();
    }

    void update(sol::state& lua) {
        for (auto& entity : get_entities()) {
            auto& cooldowns = entity.get_component<CooldownsComponent>();
            auto& attacks = entity.get_component<AttackCycleComponent>();

            if (attacks.Attacks.empty() || !cooldowns.CanPerformAction("")) continue;

            const auto [attackName, awareness] = attacks.GetNextAttack();

            if (!cooldowns.CanPerformAction(attackName)) continue;

            auto player = std::ranges::find_if(get_entities(),
               [&](auto& current) {
                   return current.template get_component<AttackCycleComponent>().Attacks.empty();
               });

            if (player == get_entities().end())
                throw std::runtime_error("EnemyAttackSystem::update : no player is registered in the game!");

            auto playerCollider = player->get_component<DamageColliderComponent>();
            auto playerTransform = player->get_component<TransformComponent>();

            auto entityCollider = entity.get_component<DamageColliderComponent>();
            auto entityTransform = entity.get_component<TransformComponent>();

            bool collision = checkAABBCollision(
            { playerTransform.position.x, playerTransform.position.y
                , playerCollider.Width, playerCollider.Height },
                { entityTransform.position.x - awareness.first
                    , entityTransform.position.y - awareness.second
                , static_cast<int32_t>(entityCollider.Width + awareness.first * 2)
                    , static_cast<int32_t>(entityCollider.Height + awareness.second * 2) });

            if (!collision) continue;

            cooldowns.PerformAction(attackName);

            if (!entity.has_component<ScriptComponent>()) continue;

            const auto& script = entity.get_component<ScriptComponent>();

            if (!script.on_perform) continue;

            lua["this"] = entity;
            (void) script.on_perform(attackName);

            attacks.PerformAttack();
        }
    }
};

#endif //ENEMY_ATTACK_SYSTEM_HPP
