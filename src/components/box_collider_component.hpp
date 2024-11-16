#ifndef BOX_COLLEGER_COMPONENT_HPP
#define BOX_COLLEGER_COMPONENT_HPP

#include <glm/glm.hpp> // GLM math library, used for vec2

/**
 * @struct BoxColliderComponent
 * @brief The BoxColliderComponent struct represents a box collider for an entity.
 */
struct BoxColliderComponent {
    int width; // width of the collider
    int height; // height of the collider
    glm::vec2 offset; // offset of the collider

    /**
     * @brief Construct a new Box Collider Component object
     * @param width The width of the collider
     * @param height The height of the collider
     * @param offset The offset of the collider
     */
    BoxColliderComponent(int width = 0, int height = 0, glm::vec2 offset = glm::vec2(0)) {
        this-> width = width;
        this->height = height;
        this->offset = offset;
    }
};


#endif // BOX_COLLEGER_COMPONENT_HPP