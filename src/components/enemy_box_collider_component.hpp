#ifndef ENEMY_COLLIDER_COMPONENT_HPP
#define ENEMY_COLLIDER_COMPONENT_HPP

#include <glm/glm.hpp> // GLM math library, used for vec2

/**
 * @struct EnemyColliderComponent
 * @brief The EnemyColliderComponent struct represents a box collider for an entity.
 */
struct EnemyColliderComponent {
    int width; // width of the collider
    int height; // height of the collider

    /**
     * @brief Construct a new Box Collider Component object
     * @param width The width of the collider
     * @param height The height of the collider
     * @param offset The offset of the collider
     */
    EnemyColliderComponent(int width = 0, int height = 0) {
        this->width = width;
        this->height = height;
    }
};


#endif // ENEMY_COLLIDER_COMPONENT_HPP