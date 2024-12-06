//
// Created by joe on 12/6/24.
//

#ifndef STATS_MANAGER_HPP
#define STATS_MANAGER_HPP

#include <string>
#include <unordered_map>
#include <optional>

#include "../components/stats_component.hpp"
#include "../ECS/ECS.hpp"

class StatsManager {
    std::unordered_map<std::string, StatsComponent> _tagToStat {};

    StatsManager() = default;
public:
    static StatsManager& GetInstance();

    /**
     * @brief Add a stat to the manager
     *
     * @param tag
     * @param stat
     */
    void AddStat(const std::string& tag, const StatsComponent& stat);

    /**
     * @brief Add stats to an entity
     *
     * @param entity
     */
    void AddStatsToEntity(Entity &entity);

    /**
     * @brief Clear all stats
     *
     */
    void Clear();

    /**
     * @brief Get the stats of an entity
     *
     * @param tag
     * @return std::optional<StatsComponent>
     */
    std::optional<StatsComponent> operator[](const std::string& tag) const;
};



#endif //STATS_MANAGER_HPP
