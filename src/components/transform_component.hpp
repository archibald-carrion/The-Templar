#ifndef TRASNFORM_COMPONENTS_HPP
#define TRASNFORM_COMPONENTS_HPP

#include <glm/glm.hpp> // GLM math library, used for vec2

/**
 * @struct TransformComponent
 * @brief The TransformComponent struct represents a transform component for an entity.
 */
struct TransformComponent {
    glm::vec2 position; // position of the entity
    glm::vec2 previous_position; // previous position of the entity
    glm::vec2 scale; // scale of the entity
    double rotation; // rotation of the entity

    /**
     * @brief Construct a new Transform Component object
     * @param position The position of the entity
     * @param scale The scale of the entity
     * @param rotation The rotation of the entity
     */
    TransformComponent(glm::vec2 position = glm::vec2(0.0f, 0.0f), glm::vec2 scale = glm::vec2(1.0f, 1.0f), double rotation = 0.0) {
        this->position = position;
        this->previous_position = position;
        this->scale = scale;
        this->rotation = rotation;
    }
};

#endif // TRASNFORM_COMPONENTS_HPP