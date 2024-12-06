#ifndef RENDER_ENEMY_BOXCOLLIDERSYSTEM_HPP
#define RENDER_ENEMY_BOXCOLLIDERSYSTEM_HPP

#include <SDL2/SDL.h>
#include "../components/enemy_box_collider_component.hpp"
#include "../components/transform_component.hpp"
#include "../ECS/ECS.hpp"

class RenderEnemyColliderSystem : public System {
public:
   RenderEnemyColliderSystem() {
       RequireComponent<EnemyColliderComponent>();
       RequireComponent<TransformComponent>();
   }

    void update(SDL_Renderer* renderer, SDL_Rect& camera) {
        for (auto entity : get_entities()) {
            const auto& collider = entity.get_component<EnemyColliderComponent>();
            const auto& transform = entity.get_component<TransformComponent>();

            SDL_Rect box = {
                static_cast<int>(transform.position.x - camera.x)-8,
                static_cast<int>(transform.position.y - camera.y)-8,
                static_cast<int>(collider.width),
                static_cast<int>(collider.height)
            };

            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderDrawRect(renderer, &box);
        }
   }
};

#endif // RENDER_ENEMY_BOXCOLLIDERSYSTEM_HPP