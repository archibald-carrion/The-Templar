//
// Created by joe on 12/3/24.
//

#ifndef DAMAGE_COLLIDER_COMPONENT_HPP
#define DAMAGE_COLLIDER_COMPONENT_HPP

#include <cstdint>

#include <glm/glm.hpp>

/**
 * @brief Component for damage collider
 */
struct DamageColliderComponent {
    int32_t Width { 0 }; // Width of the collider
    int32_t Height { 0 }; // Height of the collider
};

#endif //DAMAGE_COLLIDER_COMPONENT_HPP
