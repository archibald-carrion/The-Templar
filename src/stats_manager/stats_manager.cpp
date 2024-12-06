//
// Created by joe on 12/6/24.
//

#include "stats_manager.hpp"

#include "../components/tag_component.hpp"

StatsManager &StatsManager::GetInstance() {
    static StatsManager instance;
    return instance;
}

void StatsManager::AddStat(const std::string &tag, const StatsComponent &stat) {
    _tagToStat.insert({tag, stat});
}

void StatsManager::AddStatsToEntity(Entity &entity) {
    if (!entity.has_component<TagComponent>()) {
        return;
    }

    const auto&[tag, _] = entity.get_component<TagComponent>();
    if (!_tagToStat.contains(tag)) {
        return;
    }

    entity.add_component<StatsComponent>(_tagToStat.at(tag));
}

void StatsManager::Clear() {
    _tagToStat.clear();
}

std::optional<StatsComponent> StatsManager::operator[](const std::string &tag) const {
    if (!_tagToStat.contains(tag)) {
        return std::nullopt;
    }

    return _tagToStat.at(tag);
}