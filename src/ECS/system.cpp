#include "system.hpp"

#include <algorithm> // std::remove_if

void System::add_entity_to_system(Entity entity) {
    entities.push_back(entity);
}

void System::remove_entity_from_system(Entity entity) {
    auto it = std::remove_if(entities.begin(), entities.end(), [&entity](Entity other) {
        return entity == other;
    });
    entities.erase(it, entities.end());
}

std::vector<Entity> System::get_entities() const {
    return entities;
}

const Signature& System::get_signature() const {
    return componentSignature;
}

void System::clear_system() {
    entities.clear();
}

bool System::has_entity(const Entity& entity) const {
    return std::ranges::any_of(entities
        , [&](const Entity &other) { return entity == other; });
}
