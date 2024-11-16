#include "ECS.hpp"

Registry::Registry() {
    //std::cout<<"[REGISTRY] Constructor" << std::endl;
}
    
Registry::~Registry() {
    //std::cout<<"[REGISTRY] Destructor" << std::endl;
}

Entity Registry::create_entity(){
    std::size_t entity_id;

    // if there are free ids, use one of them
    if(!free_ids.empty()){
        entity_id = free_ids.front();
        free_ids.pop_front();
    }else{
        // otherwise, create a new id
        entity_id = num_entities++;
        bool is_resize_needed = entity_id >= entityComponentSignatures.size();
        if(is_resize_needed){
            entityComponentSignatures.resize(entity_id + 100);
        }
    }

    Entity entity(entity_id);
    entity.registry = this;
    entities_to_be_added.insert(entity);
    return entity;
}

void Registry::kill_entity(Entity entity){
    entities_to_be_killed.insert(entity);
}

void Registry::add_entity_to_system(Entity entity){
    const int entity_id = entity.get_id();
    const Signature& entity_component_signature = entityComponentSignatures[entity_id];

    for(auto& system : systems){
        const auto& system_component_signature = system.second->get_signature();
        bool is_compatible = (entity_component_signature & system_component_signature) == system_component_signature;
        if(is_compatible){
            system.second->add_entity_to_system(entity);
        }
    }
}

void Registry::remove_entity_from_system(Entity entity){
    for (auto& system : systems){
        system.second->remove_entity_from_system(entity);
    }
}

void Registry::update(){
    for (auto& entity : entities_to_be_added){
        add_entity_to_system(entity);
    }
    entities_to_be_added.clear();

    for(auto& entity: entities_to_be_killed) {
        remove_entity_from_system(entity);
        entityComponentSignatures[entity.get_id()].reset();
        free_ids.push_back(entity.get_id());

        //add id to free ids deque
    }
    entities_to_be_killed.clear();

}

void Registry::clear_all_entities() {
    // Remove all entities from systems
    for(int i = 0; i < num_entities; i++) {
        Entity entity(i);
        remove_entity_from_system(entity);
    }

    // Clear the component pools
    for (auto& pool : componentsPools) {
        if (pool) {
            pool->clear();
        }
    }

    // Resize and reset all signatures
    entityComponentSignatures.clear();
    entityComponentSignatures.resize(100);

    // Clear entity management containers
    entities_to_be_added.clear();
    entities_to_be_killed.clear();

    // Reset free IDs
    free_ids.clear();

    // Reset entity counter
    num_entities = 0;
}

void Entity::kill() {
    registry->kill_entity(*this);
}

