#ifndef ECS_HPP
#define ECS_HPP

#include <bitset> 
#include <memory>
#include <unordered_map>
#include <set>
#include <typeindex>
#include <deque>
#include <vector>
#include <iostream>
#include "../utils/Pool.hpp"

#include "entity.hpp"
#include "system.hpp"

/**
 * @class Registry
 * @brief The Registry class represents the registry in the ECS system.
 */
class Registry {
private:
    std::vector<std::shared_ptr<IPool>> componentsPools; // pools of components
    std::vector<Signature> entityComponentSignatures; // signatures of the components of the entities

    std::unordered_map<std::type_index, std::shared_ptr<System>> systems; // systems in the registry
    std::set<Entity> entities_to_be_added; // entities to be added to the registry
    std::set<Entity> entities_to_be_killed; // entities to be deleted from the registry

    std::deque<int> free_ids; // deque containing free ids

public: 
    int num_entities = 0; // current number of entities in the registry

    /**
    * @brief Constructs a new Registry object.
    */
    Registry();
    
    /**
    * @brief Destroys the Registry object.
    */
    ~Registry();

    /**
    * @brief Updates the registry. This function should be called periodically to process any changes within the registry.
    */
    void update();
    
    /**
    * @brief Creates a new entity within the registry. 
    * @return The created entity.
    */
    Entity create_entity();

    /**
     * @brief Kills (removes) an entity from the registry.
     * @param entity The entity to be removed.
     */
    void kill_entity(Entity entity);

    /**
     * @brief Adds a component of type TComponent to the specified entity.
     * @param entity The entity to which the component will be added.
     * @param args The arguments to pass to the component constructor.
     */
    template <typename TComponent, typename... TArgs>
    void add_component(Entity entity, TArgs&&... args);

    /**
     * @brief Removes a component of type TComponent from the specified entity.
     * @param entity The entity from which the component will be removed.
     */
    template <typename TComponent>
    void remove_component(Entity entity);

    /**
     * @brief Checks if the specified entity has a component of type TComponent.
     * @param entity The entity to check.
     * @return true if the entity has the component, false otherwise.
     */
    template <typename TComponent>
    bool has_component(Entity entity);

    /**
     * @brief Gets the component of type TComponent from the specified entity.
     * @param entity The entity from which the component will be retrieved.
     * @return The component.
     */    
    template <typename TComponent>
    TComponent& get_component(Entity entity) const;

    /**
     * @brief Adds a system of type TSystem to the registry.
     * @param args The arguments to pass to the system constructor.
     */
    template <typename TSystem, typename... TArgs>
    void add_system(TArgs&&... args);

    /**
     * @brief Removes a system of type TSystem from the registry.
     * @param entity The entity from which the system will be removed.
     */
    template <typename TSystem>
    void remove_system(Entity entity);

    /**
     * @brief Checks if the registry has a system of type TSystem.
     * @param entity The entity to check.
     * @return true if the registry has the system, false otherwise.
     */
    template <typename TSystem>
    bool has_system(Entity entity);

    /**
     * @brief Gets the system of type TSystem from the registry.
     * @return The system.
     */
    template <typename TSystem>
    TSystem& get_system() const;

    /**
     * @brief Adds an entity to the system
     * @param entity The entity to be added
     */
    void add_entity_to_system(Entity entity);

    /**
     * @brief Removes an entity from the system
     * @param entity The entity to be removed
     */
    void remove_entity_from_system(Entity entity);

    /**
     * @brief Clears all entities from the registry
     */
    void clear_all_entities();

};

template <typename TComponent, typename... TArgs>
void Registry::add_component(Entity entity, TArgs&&... args) {

    const size_t component_id = Component<TComponent>::get_id();
    const int entity_id = entity.get_id();
    if (component_id >= componentsPools.size()) {
        componentsPools.resize(component_id + 10);
    }

    if(!componentsPools[component_id]){
        std::shared_ptr<Pool<TComponent>> new_component_pool =
            std::make_shared<Pool<TComponent>>();
        componentsPools[component_id] = new_component_pool;
    }

    std::shared_ptr<Pool<TComponent>> component_pool =
        std::static_pointer_cast<Pool<TComponent>>(componentsPools[component_id]);

    if (entity_id >= component_pool->get_size()) {
        component_pool->resize(entity_id + 10);
    }

    TComponent new_component(std::forward<TArgs>(args)...);

    component_pool->set(entity_id, new_component);
    entityComponentSignatures[entity_id].set(component_id);

    // std::cout << "component added to Registry, component id: " << component_id << " to entity :" << entity_id << std::endl;
}

template <typename TComponent>
void Registry::remove_component(Entity entity){
    const int component_id = Component<TComponent>::get_id();
    const int entity_id = entity.get_id();

    // Check if the component exists
    if (static_cast<size_t>(component_id) >= componentsPools.size()) {
        return;
    }

    // Check if the entity has the component
    if(!componentsPools[component_id]){
        return;
    }

    entityComponentSignatures[entity_id].set(component_id, false);
}

template <typename TComponent>
bool Registry::has_component(Entity entity) {
    const int component_id = Component<TComponent>::get_id();
    const int entity_id = entity.get_id();

    // Check if the component exists
    if (static_cast<size_t>(component_id) >= componentsPools.size()) {
        return false;
    }
    // Check if the entity has the component
    if(!componentsPools[component_id]){
        return false;
    }

    return entityComponentSignatures[entity_id].test(component_id);
}

template <typename TComponent>
TComponent& Registry::get_component(Entity entity) const{
    const size_t component_id = Component<TComponent>::get_id();
    const int entity_id = entity.get_id();

    // Check if the component exists
    if (component_id >= componentsPools.size()) {
        throw std::runtime_error("Component does not exist");
    }

    // Check if the entity has the component
    if(!componentsPools[component_id]){
        throw std::runtime_error("Component does not exist");
    }

    auto component_pool = std::static_pointer_cast<Pool<TComponent>>(componentsPools[component_id]);

    return component_pool->get(entity_id);
}

template <typename TSystem, typename... TArgs>
void Registry::add_system(TArgs&&... args) {
    std::shared_ptr<TSystem> new_system;
    
    if constexpr (sizeof...(TArgs) == 0) {
        new_system = std::make_shared<TSystem>();
    } else {
        new_system = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
    }
    
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), new_system));
}

template <typename TSystem>
void Registry::remove_system(Entity entity) {
    auto system = systems.find(std::type_index(typeid(TSystem)));
    // Check if the system exists
    if (system == systems.end()) {
        return;
    }
    systems.erase(system);
}

template <typename TSystem>
bool Registry::has_system(Entity entity){
    auto system = systems.find(std::type_index(typeid(TSystem)));
    return system != systems.end();
}


template <typename TSystem>
TSystem& Registry::get_system() const{
    auto system = systems.find(std::type_index(typeid(TSystem)));
    // Check if the system exists
    if (system == systems.end()) {
        throw std::runtime_error("System does not exist");
    }
    return *std::static_pointer_cast<TSystem>(system->second); // get the system from the iterator because it is a pair
}

template <typename TComponent, typename... TArgs>
void Entity::add_component(TArgs&&... args) {
    registry->add_component<TComponent>(*this, std::forward<TArgs>(args)...);
}

template <typename TComponent>
void Entity::remove_component(){
    registry->remove_component<TComponent>(*this);
}

template <typename TComponent>
bool Entity::has_component(){
    return registry->has_component<TComponent>(*this);
}

template <typename TComponent>
TComponent& Entity::get_component() const{
    return registry->get_component<TComponent>(*this);
}

#endif // ECS_HPP