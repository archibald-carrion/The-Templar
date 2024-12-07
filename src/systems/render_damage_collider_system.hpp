//
// Created by joe on 12/4/24.
//

#ifndef RENDER_DAMAGE_COLLIDER_SYSTEM_HPP
#define RENDER_DAMAGE_COLLIDER_SYSTEM_HPP

#include <SDL2/SDL.h>
#include "../components/damage_collider_component.hpp"
#include "../components/transform_component.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief The RenderDamageColliderSystem class
 * The RenderDamageColliderSystem class is a class for rendering damage colliders.
 */
class RenderDamageColliderSystem : public System {
public:

    /**
     * @brief Construct a new Render Damage Collider System object
     */
    RenderDamageColliderSystem() {
        RequireComponent<DamageColliderComponent>();
        RequireComponent<TransformComponent>();
    }

    /**
     * @brief Update the render damage collider system
     * @param renderer The SDL renderer
     * @param camera The camera
     */
    void update(SDL_Renderer* renderer, SDL_Rect& camera) {
        for (auto entity : get_entities()) {
            const auto& collider = entity.get_component<DamageColliderComponent>();
            const auto& transform = entity.get_component<TransformComponent>();

            SDL_Rect box = {
                static_cast<int>(transform.position.x - camera.x) - 4,
                static_cast<int>(transform.position.y - camera.y) - 4,
                static_cast<int>(collider.Width) + 8,
                static_cast<int>(collider.Height) + 8
            };

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawRect(renderer, &box);
        }
    }
};

#endif //RENDER_DAMAGE_COLLIDER_SYSTEM_HPP
