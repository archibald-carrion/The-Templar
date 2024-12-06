//
// Created by joe on 12/5/24.
//

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cstdint>

struct Info {
    float X;
    float Y;
    int32_t Width;
    int32_t Height;
};

static bool checkAABBCollision(const Info& a, const Info& b) {
    return
        a.X < b.X + b.Width &&
        a.X + a.Width > b.X &&
        a.Y < b.Y + b.Height &&
        a.Y + a.Height > b.Y
    ;
}

#endif //UTILITIES_HPP
