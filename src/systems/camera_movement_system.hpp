#ifndef CAMERA_MOVEMENT_SYSTEM_HPP
#define CAMERA_MOVEMENT_SYSTEM_HPP

#include "../ECS/ECS.hpp"   // Entity, System
#include <SDL2/SDL.h>       // SDL library for window creation and rendering
#include "../game/game.hpp" // Game

#include "../components/camera_follow_component.hpp" // CameraFollowComponent
#include "../components/transform_component.hpp"     // TransformComponent

/***
 * @brief CameraMovementSystem class
 * The CameraMovementSystem class is a class for managing camera movement.
 */
class CameraMovementSystem : public System
{
public:
    /***
     * @brief Constructor for CameraMovementSystem
     */
    CameraMovementSystem()
    {
        RequireComponent<CameraFollowComponent>();
        RequireComponent<TransformComponent>();
    }

    /***
     * @brief Update the camera movement system, this will update the camera position based on the player position
     * @param camera The camera rectangle
     */
    void update(SDL_Rect &camera)
    {
        for (auto entity : get_entities())
        {
            const auto &transform = entity.get_component<TransformComponent>();

            // Centramos la cámara en el jugador
            camera.x = static_cast<int>(transform.position.x) - (camera.w / 2);
            camera.y = static_cast<int>(transform.position.y) - (camera.h / 2);

            // Ancho y alto total del mapa en píxeles
            int map_width_pixels = Game::get_instance().map_width;   // 3000
            int map_height_pixels = Game::get_instance().map_height; // 3000

            if (map_width_pixels > camera.w)
            {
                camera.x = std::max(0, std::min(camera.x, map_width_pixels - camera.w));
            }
            else
            {
                camera.x = (map_width_pixels - camera.w) / 2;
            }

            if (map_height_pixels > camera.h)
            {
                camera.y = std::max(0, std::min(camera.y, map_height_pixels - camera.h));
            }
            else
            {
                camera.y = (map_height_pixels - camera.h) / 2;
            }
        }
    }
};

#endif // CAMERA_MOVEMENT_SYSTEM_HPP