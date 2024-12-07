//
// Created by joe on 12/5/24.
//

#ifndef ATTACK_CYCLE_COMPONENT_HPP
#define ATTACK_CYCLE_COMPONENT_HPP

#include <string>
#include <vector>

/**
 * @brief Represents an attack
 */
struct Attack {
    std::string Name; // Name of the attack
    std::pair<size_t, size_t> AwarenessX; // Awareness X
};

/**
 * @brief Component for cycle of different attacks
 */
struct AttackCycleComponent {
    std::string ProjectileScriptPath; // Projectile script path
    double RangeDistance = 0; // Range distance
    std::vector<Attack> Attacks {}; // List of attacks
    size_t CurrentAttack = 0; // Current attack

    /**
     * @brief Get the next attack
     * @return Attack
     */
    Attack GetNextAttack() {
        return Attacks[CurrentAttack];
    }

    /**
     * @brief Perform the next attack
     */
    void PerformAttack() {
        CurrentAttack++;
        if (CurrentAttack >= Attacks.size())
            CurrentAttack = 0;
    }
};


#endif //ATTACK_CYCLE_COMPONENT_HPP
