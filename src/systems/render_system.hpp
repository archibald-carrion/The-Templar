#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <iostream> // std::cout
#include "SDL2/SDL.h" // SDL library for window creation and rendering
#include "../assets_manager/assets_manager.hpp" // AssetsManager
#include "../components/sprite_component.hpp" // SpriteComponent
#include "../components/transform_component.hpp" // TransformComponent
#include "../ECS/ECS.hpp" // System

/***
 * @brief RenderSystem class
 * The RenderSystem class is a class for rendering entities.
 */
class RenderSystem: public System {
public:

    /***
     * @brief Constructor for RenderSystem
     */
    RenderSystem() {
        // std::cout<<"[RENDERSYSTEM] constructor"<<std::endl;
        RequireComponent<SpriteComponent>();
        RequireComponent<TransformComponent>();
    }

    /***
     * @brief Update the render system, this will render the entities to the screen
     * @param renderer The SDL renderer
     * @param asset_manager The asset manager
     * @param camera The camera rectangle
     */
    void update(
        SDL_Renderer* renderer,
        const std::unique_ptr<AssetsManager>& asset_manager,
        SDL_Rect& camera) {
        
        // loop through all the entities
        for(auto entity: get_entities()) {
            const auto sprite = entity.get_component<SpriteComponent>();
            const auto transform = entity.get_component<TransformComponent>();

            SDL_Rect src_rect = sprite.src_rect;
            SDL_Rect dst_rect = {
                static_cast<int>(transform.position.x - camera.x),
                static_cast<int>(transform.position.y - camera.y),
                static_cast<int>(sprite.width * transform.scale.x),
                static_cast<int>(sprite.height * transform.scale.y)
            };

            SDL_RenderCopyEx(
                renderer, 
                asset_manager->get_texture(sprite.texture_id),
                &src_rect, 
                &dst_rect, 
                transform.rotation,
                NULL, // is centered
                (sprite.flip) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE // flip the sprite if needed
            );
        }
    }
};


#endif // RENDER_SYSTEM_HPP