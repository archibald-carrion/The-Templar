//
// Created by joe on 12/1/24.
//

#ifndef STATE_COMPONENT_HPP
#define STATE_COMPONENT_HPP

#include <cstdint>

/**
 * @struct StateComponent
 * @brief The StateComponent struct represents a state component for an entity.
 */
struct StateComponent {
    int8_t state { 1 };
    int8_t next_state { -1 };
    explicit StateComponent(const int8_t state) : state(state), next_state(state) {}
    StateComponent() = default;
};

#endif //STATE_COMPONENT_HPP
