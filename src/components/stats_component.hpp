//
// Created by joe on 12/6/24.
//

#ifndef STATS_COMPONENTS_HPP
#define STATS_COMPONENTS_HPP

#include <cstdint>
/**
 * @brief Component for the stats of an entity
 *
 */
struct StatsComponent {
    int32_t Points { 0 };
    int32_t Health { 0 };
    int32_t Damage { 0 };

    int32_t UltCounter { 0 };
};

#endif //STATS_COMPONENTS_HPP
