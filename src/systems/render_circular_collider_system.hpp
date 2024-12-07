#ifndef RENDERCIRCULARCOLLIDERSYSTEM_HPP
#define RENDERCIRCULARCOLLIDERSYSTEM_HPP

#include <SDL2/SDL.h>
#include "../components/circle_collider_component.hpp"
#include "../components/transform_component.hpp"
#include "../ECS/ECS.hpp"
#include <cmath>

/**
 * @brief The RenderCircularColliderSystem class
 * The RenderCircularColliderSystem class is a class for rendering circular colliders.
 */
class RenderCircularColliderSystem : public System {
public:

    /**
     * @brief Construct a new Render Circular Collider System object
     */
    RenderCircularColliderSystem() {
        RequireComponent<CircleColliderComponent>();
        RequireComponent<TransformComponent>();
    }

    /**
     * @brief Update the render circular collider system
     * @param renderer The SDL renderer
     * @param camera The camera
     */
    void update(SDL_Renderer* renderer, SDL_Rect& camera) {
        for (auto entity : get_entities()) {
            const auto& collider = entity.get_component<CircleColliderComponent>();
            const auto& transform = entity.get_component<TransformComponent>();

            // Calculate the screen position of the circle, adjusted for camera
            int screenX = static_cast<int>(transform.position.x - camera.x);
            int screenY = static_cast<int>(transform.position.y - camera.y);

            // Set render color to red (like the box collider system)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

            // Draw circle by drawing multiple line segments
            for (int w = 0; w < collider.radius * 2; w++) {
                for (int h = 0; h < collider.radius * 2; h++) {
                    int dx = collider.radius - w; // horizontal offset
                    int dy = collider.radius - h; // vertical offset
                    
                    // Check if point is within the circle
                    if (dx*dx + dy*dy <= collider.radius*collider.radius) {
                        SDL_RenderDrawPoint(renderer, screenX - collider.radius + w, screenY - collider.radius + h);
                    }
                }
            }
        }
    }
};

#endif // RENDERCIRCULARCOLLIDERSYSTEM_HPP