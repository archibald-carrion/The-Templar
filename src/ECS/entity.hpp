#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "component.hpp"

/**
 * @class Entity
 * @brief The Entity class represents an entity in the ECS system.
 */
class Entity {
private:
    int id; // id of the entity

public:
    /**
     * @brief Construct a new Entity object
     * @param id The id of the entity
     */
    Entity(int id) : id(id) {}
    
    /**
     * @brief Get the id of the entity
     * @return int The id of the entity
     */
    int get_id() const;

    /**
     * @brief Kill the entity
     */
    void kill();

    /**
     * @brief Check if the entity is alive
     * @return true if the entity is alive, false otherwise
     */
    bool operator==(const Entity& other) const {
        return id == other.id;
    }

    /**
     * @brief Check if the entity is not alive
     * @return true if the entity is not alive, false otherwise
     */
    bool operator!=(const Entity& other) const {
        return id != other.id;
    }

    /**
     * @brief Check if the entity is greater than another entity
     * @return true if the entity is greater than another entity, false otherwise
     */
    bool operator>(const Entity& other) const {
        return id > other.id;
    }

    /**
     * @brief Check if the entity is less than another entity
     * @return true if the entity is less than another entity, false otherwise
     */
    bool operator<(const Entity& other) const {
        return id < other.id;
    }

    /**
     * @brief Check if the entity is greater than or equal to another entity
     * @return true if the entity is greater than or equal to another entity, false otherwise
     */
    template <typename TComponent, typename... TArgs>
    void add_component(TArgs&&... args);

    /**
     * @brief Remove a component from the entity
     */
    template <typename TComponent>
    void remove_component();

    /**
     * @brief Check if the entity has a component
     * @return true if the entity has a component, false otherwise
     */
    template <typename TComponent>
    bool has_component();

    /**
     * @brief Get a component from the entity
     * @return TComponent& The component
     */
    template <typename TComponent>
    TComponent& get_component() const;

    class Registry* registry;
};


#endif // ENTITY_HPP