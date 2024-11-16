#ifndef RENDER_TEXT_SYSTEM_HPP
#define RENDER_TEXT_SYSTEM_HPP

#include <memory> // std::unique_ptr
#include <SDL2/SDL.h> // SDL library for window creation and rendering
#include <SDL2/SDL_ttf.h> // SDL ttf library for rendering text
#include "../components/text_component.hpp" // TextComponent
#include "../components/transform_component.hpp" // TransformComponent
#include "../assets_manager/assets_manager.hpp" // AssetsManager
#include "../ECS/ECS.hpp" // System

/***
 * @brief RenderTextSystem class
 * The RenderTextSystem class is a class for rendering text entities.
 */
class RenderTextSystem : public System {
public:

    /***
     * @brief Constructor for RenderTextSystem
     */
    RenderTextSystem() {
        RequireComponent<TextComponent>();
        RequireComponent<TransformComponent>();
    }

    /***
     * @brief Update the render text system, this will render the text entities to the screen
     * @param renderer The SDL renderer
     * @param asset_manager The asset manager
     */
    void update(SDL_Renderer* renderer, const std::unique_ptr<AssetsManager>& assets_manager) {
        // loop through all the entities
        for(auto entity : get_entities()) {
            auto& text = entity.get_component<TextComponent>();
            auto& transform = entity.get_component<TransformComponent>();

        	// create the surface
            SDL_Surface* surface = TTF_RenderText_Blended(
                assets_manager->get_font(text.font_id),
                text.text.c_str(),
                text.color
            );

            text.width = surface->w;
            text.height = surface->h;
            // create the texture
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            // free the surface
            SDL_FreeSurface(surface);

            SDL_Rect destionation_rect = {
                static_cast<int>(transform.position.x),
                static_cast<int>(transform.position.y),
                text.width * static_cast<int>(transform.scale.x),
                text.height  * static_cast<int>(transform.scale.y)
            };

            // render the texture
            SDL_RenderCopy(renderer, texture, NULL, &destionation_rect);
            SDL_DestroyTexture(texture);
        }
    }
};

#endif // RENDER_TEXT_SYSTEM_HPP