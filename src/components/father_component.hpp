//
// Created by joe on 12/6/24.
//

#ifndef FATHER_COMPONENT_HPP
#define FATHER_COMPONENT_HPP

#include "../ECS/ECS.hpp"

struct FatherComponent {
    std::vector<Entity> Children;
};

#endif //FATHER_COMPONENT_HPP
