#ifndef COLLISION_EVENT_HPP
#define COLLISION_EVENT_HPP

#include "../event_manager/event_manager.hpp" // Event
#include "../ECS/ECS.hpp" // Entity

/**
 * @class CollisionEvent
 * @brief The CollisionEvent class represents a collision event.
 */
class CollisionEvent : public Event {
public:
    Entity a; // entity a
    Entity b; // entity b

    /**
     * @brief Construct a new CollisionEvent object
     * @param a The entity a
     * @param b The entity b
     */
    CollisionEvent(Entity a, Entity b): a(a), b(b) {
        
    }
};


#endif // COLLISION_EVENT_HPP