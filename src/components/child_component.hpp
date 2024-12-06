//
// Created by joe on 12/6/24.
//

#ifndef CHILD_COMPONENT_HPP
#define CHILD_COMPONENT_HPP

#include "../ECS/ECS.hpp"

struct ChildComponent {
  std::optional<Entity> Father { std::nullopt };

  ChildComponent(const Entity father) : Father(father) {}

  ChildComponent() = default;
};

#endif //CHILD_COMPONENT_HPP
