#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "event.hpp"  // Event
#include <functional> // std::invoke
#include <list> // std::list
#include <map> // std::map
#include <memory> // std::unique_ptr
#include <iostream> // std::cout
#include <typeindex> // std::type_index

/**
 * @class IEventCallback
 * @brief The IEventCallback class is an interface for the EventCallback class.
 */
class IEventCallback {
private:
    /**
     * @brief Call the event
     * @param e The event
     */
    virtual void call(Event& e) = 0;

public:
    /**
     * @brief Execute the event
     * @param e The event
     */
    virtual ~IEventCallback() = default;

    /**
     * @brief Execute the event
     * @param e The event
     */
    void execute(Event& e) {
        call(e);
    }
};


/**
 * @class EventCallback
 * @brief The EventCallback class is a template class for the event callbacks.
 */
template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
private:
    typedef void(TOwner::*CallbackFunction)(TEvent&); // callback function type
    TOwner* owner_instance; // owner instance
    CallbackFunction callback_function; // callback function

    /**
     * @brief Call the event
     * @param e The event
     */
    virtual void call(Event& e) override {
        std::invoke(callback_function, owner_instance, static_cast<TEvent&>(e));
    }

public: 
    /**
     * @brief Construct a new EventCallback object
     * @param owner_instance The owner instance
     * @param callback_function The callback function
     */
    EventCallback(TOwner* owner_instance, CallbackFunction callback_function) {
        this->callback_function = callback_function;
        this->owner_instance = owner_instance;
    }
};


typedef std::list<std::unique_ptr<IEventCallback>> handler_list; // handler list

/**
 * @class EventManager
 * @brief The EventManager class is a class for managing events.
 */
class EventManager {
private:
    std::map<std::type_index, std::unique_ptr<handler_list>> subscribers; // subscribers
public:
    /**
     * @brief Construct a new EventManager object
     */
    EventManager() {
        //std::cout << "[EVENTMANAGER] EventManager constructor" << std::endl;
    }

    /**
     * @brief Destroy the EventManager object
     */
    ~EventManager() {
        //std::cout << "[EVENTMANAGER] EventManager destructor" << std::endl;
    }

    /**
     * @brief Reset the event manager
     */
    void reset() {
        subscribers.clear();
    }

    /**
     * @brief Subscribe to an event
     * @param owner_instance The owner instance
     * @param callbackFunction The callback function
     */
    template <typename TEvent, typename TOwner>
    void subscribe_to_event(TOwner* owner_instance, void (TOwner::*callbackFunction) (TEvent&)) {
        if(!subscribers[typeid(TEvent)].get()) {
            subscribers[typeid(TEvent)] = std::make_unique<handler_list>();
        }
        auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(owner_instance, callbackFunction);
        subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    }

    /**
     * @brief Emit an event
     * @param args The arguments
     */
    template <typename TEvent, typename... TArgs>
    void emit_event(TArgs&&... args){
        auto handlers = subscribers[typeid(TEvent)].get();
        if(handlers) {
            // loop through all the handlers
            for (auto it = handlers->begin(); it != handlers->end(); it++) {
                auto handler = it->get();
                TEvent event (std::forward<TArgs>(args)...);
                handler->execute(event);
            }
        }
    }
};

#endif // EVENT_MANAGER_HPP