#ifndef CIRCLE_COLLISION_COMPONENT_HPP
#define CIRCLE_COLLISION_COMPONENT_HPP

/**
 * @struct CircleColliderComponent
 * @brief The CircleColliderComponent struct represents a circle collider for an entity.
 */
struct CircleColliderComponent
{
    int radius; // radius of the collider
    int width; // width of the collider
    int height; // height of the collider

    /**
     * @brief Construct a new Circle Collider Component object
     * @param radius The radius of the collider
     * @param width The width of the collider
     * @param height The height of the collider
     */
    CircleColliderComponent(int radius = 0, int width=0, int height = 0) {
        this->radius = radius;
        this->width = width;
        this->height = height;
    }
};


#endif // CIRCLE_COLLISION_COMPONENT_HPP