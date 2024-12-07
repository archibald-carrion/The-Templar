//
// Created by joe on 12/6/24.
//

#ifndef CHILD_COMPONENT_HPP
#define CHILD_COMPONENT_HPP

#include "../ECS/ECS.hpp" // Entity component system

/**
 * @brief Component for child entities
 */
struct ChildComponent {
  std::optional<Entity> Father { std::nullopt }; // Father entity

  /**
   * @brief Construct a new Child Component object
   * @param father The father entity
   */
  ChildComponent(const Entity father) : Father(father) {}

  /**
   * @brief Construct a new Child Component object
   */
  ChildComponent() = default;
};

#endif //CHILD_COMPONENT_HPP
