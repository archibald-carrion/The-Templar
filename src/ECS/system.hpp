#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <bitset> // std::bitset
#include <vector> // std::vector
#include "entity.hpp" // Entity

const unsigned int MAX_COMPONENTS = 64; // Maximum number of components an entity can have
typedef std::bitset<MAX_COMPONENTS> Signature; // Signature is a bitset that represents the components an entity has



/**
 * @class System
 * @brief The System class represents a system in the ECS system.
 */
class System {
private:
    Signature componentSignature; // signature of the components the system operates on
    std::vector<Entity> entities; // entities on which this system operates

public:
    /**
     * @brief Construct a new System object
     */
    System()= default;

    /**
     * @brief Destroy the System object
     */
    ~System()= default;

    /**
     * @brief Update the system
     */
    void add_entity_to_system(Entity entity);

    /**
     * @brief Update the system
     */
    void remove_entity_from_system(Entity entity);

    /**
     * @brief Update the system
     */
    std::vector<Entity> get_entities() const;

    /**
     * @brief Update the system
     */
    const Signature& get_signature() const;

    /**
     * @brief Update the system
     */
    template<typename TComponent>
    void RequireComponent();
};


template<typename TComponent>
void System::RequireComponent() {
    const int component_id = Component<TComponent>::get_id();
    componentSignature.set(component_id);
}


#endif // SYSTEM_HPP