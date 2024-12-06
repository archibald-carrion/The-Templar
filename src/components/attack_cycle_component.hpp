//
// Created by joe on 12/5/24.
//

#ifndef ATTACK_CYCLE_COMPONENT_HPP
#define ATTACK_CYCLE_COMPONENT_HPP

#include <string>
#include <vector>

/**
 * @brief Represents an attack
 *
 */
struct Attack {
    std::string Name;
    std::pair<size_t, size_t> AwarenessX;
};

/**
 * @brief Component for cycle of different attacks
 *
 */
struct AttackCycleComponent {
    std::string ProjectileScriptPath;
    double RangeDistance = 0;
    std::vector<Attack> Attacks {};

    size_t CurrentAttack = 0;

    Attack GetNextAttack() {
        return Attacks[CurrentAttack];
    }

    void PerformAttack() {
        CurrentAttack++;
        if (CurrentAttack >= Attacks.size())
            CurrentAttack = 0;
    }
};


#endif //ATTACK_CYCLE_COMPONENT_HPP
