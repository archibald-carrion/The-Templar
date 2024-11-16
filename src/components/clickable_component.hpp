#ifndef CLICKABLE_COMPONENT_HPP
#define CLICKABLE_COMPONENT_HPP

/**
 * @struct ClickableComponent
 * @brief The ClickableComponent struct represents a clickable component for an entity.
 */
struct ClickableComponent {
    bool is_clicked; // flag to indicate if the component is clicked
    bool is_hovered; // flag to indicate if the component is hovered

    /**
     * @brief Construct a new Clickable Component object
     */
    ClickableComponent() {
        is_clicked = false;
        is_hovered = false;
    }
};

#endif // CLICKABLE_COMPONENT_HPP