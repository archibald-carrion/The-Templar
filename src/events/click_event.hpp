#ifndef CLICK_EVENT_HPP
#define CLICK_EVENT_HPP

#include "../ECS/ECS.hpp" // Entity
#include "../event_manager/event.hpp" // Event

/**
 * @class ClickEvent
 * @brief The ClickEvent class represents a click event.
 */
class ClickEvent : public Event {
public:
    int button_code; // button code
    int position_x; // x position
    int position_y; // y position

    /**
     * @brief Construct a new ClickEvent object
     * @param button_code The button code
     * @param position_x The x position
     * @param position_y The y position
     */
    ClickEvent(int button_code, int position_x, int position_y) {
        this->button_code = button_code;
        this->position_x = position_x;
        this->position_y = position_y;
    }
};

#endif // CLICK_EVENT_HPP