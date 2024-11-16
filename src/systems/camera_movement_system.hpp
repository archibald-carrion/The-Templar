#ifndef CAMERA_MOVEMENT_SYSTEM_HPP
#define CAMERA_MOVEMENT_SYSTEM_HPP

#include "../ECS/ECS.hpp" // Entity, System
#include <SDL2/SDL.h> // SDL library for window creation and rendering
#include "../game/game.hpp" // Game

#include "../components/camera_follow_component.hpp" // CameraFollowComponent
#include "../components/transform_component.hpp" // TransformComponent

/***
 * @brief CameraMovementSystem class
 * The CameraMovementSystem class is a class for managing camera movement.
 */
class CameraMovementSystem : public System {
public:

    /***
     * @brief Constructor for CameraMovementSystem
     */
    CameraMovementSystem() {
        RequireComponent<CameraFollowComponent>();
        RequireComponent<TransformComponent>();
    }

    /***
     * @brief Update the camera movement system, this will update the camera position based on the player position
     * @param camera The camera rectangle
     */
    void update(SDL_Rect& camera){
        // loop through all the entities
        for(auto entity: get_entities()) {
            const auto& tranform = entity.get_component<TransformComponent>();

            if(tranform.position.x + (camera.w /2) < static_cast<float>(Game::get_instance().map_width)) {
                camera.x = static_cast<int>(tranform.position.x) - (camera.w/2);
            }

            if(tranform.position.y + (camera.w /2) < static_cast<float>(Game::get_instance().map_height)) {
                camera.y = static_cast<int>(tranform.position.y) - (camera.h/2);
            }

            camera.x =camera.x < 0 ? 0:camera.x;
            camera.y =camera.y < 0 ? 0:camera.y;

        }
    }
};

#endif // CAMERA_MOVEMENT_SYSTEM_HPP