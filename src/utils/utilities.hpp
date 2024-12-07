//
// Created by joe on 12/5/24.
//

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cstdint>

/**
 * @brief The Info struct
 * The Info struct represents the information of an entity.
 */
struct Info {
    float X;
    float Y;
    int32_t Width;
    int32_t Height;
};

/**
 * @brief Check if two entities are colliding.
 * @param a The first entity.
 * @param b The second entity.
 * @return True if the entities are colliding, false otherwise.
 */
static bool checkAABBCollision(const Info& a, const Info& b) {
    return
        a.X < b.X + b.Width &&
        a.X + a.Width > b.X &&
        a.Y < b.Y + b.Height &&
        a.Y + a.Height > b.Y
    ;
}

#endif //UTILITIES_HPP
