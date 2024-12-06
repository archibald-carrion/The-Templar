//
// Created by joe on 12/6/24.
//

#ifndef STATS_SYSTEM_HPP
#define STATS_SYSTEM_HPP

#include <ranges>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../ECS/ECS.hpp"
#include "../components/tag_component.hpp"
#include "../components/stats_component.hpp"

inline auto surfaceDeleter = [](SDL_Surface* surface) {
    SDL_FreeSurface(surface);
};

inline auto textureDeleter = [](SDL_Texture* texture) {
    SDL_DestroyTexture(texture);
};

inline auto fontDeleter = [](TTF_Font* font) {
    if (!font) return ;
    TTF_CloseFont(font);
};

class StatsSystem : public System {
    std::unique_ptr<TTF_Font, decltype(fontDeleter)> font;
    const int FONT_SIZE = 38;
    const char* FONT_PATH = "./assets/fonts/ARCADECLASSIC.TTF";
    const int MARGIN = 20;

public:
    StatsSystem() {
        RequireComponent<TagComponent>();
        RequireComponent<StatsComponent>();
        font.reset(TTF_OpenFont(FONT_PATH, FONT_SIZE));
    }

    void update(SDL_Renderer* renderer) {
        std::vector<Entity>& entities = get_entities();

        auto found = std::ranges::find_if(entities, [&](Entity& entity) {
            return entity.get_component<TagComponent>().tag == "player";
        });

        if (found == entities.end()) return;


        auto& [points, health, _, ult] = found->get_component<StatsComponent>();

        std::stringstream buffer;
        buffer << "Score    " << points;
        std::string pointsStr = buffer.str();
        buffer.str(""); buffer.clear();
        buffer << "Health   " << health;
        std::string healthStr = buffer.str();
        buffer.str(""); buffer.clear();
        buffer << "Ult   " << ult;
        std::string ultStr = buffer.str();

        int32_t window_width, window_height;
        SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

        std::unique_ptr<SDL_Surface, decltype(surfaceDeleter)> surface (
            TTF_RenderText_Blended(
            font.get(),
            pointsStr.c_str(),
            SDL_Color{255, 255, 255, 255}  // White color
        ), surfaceDeleter);

        std::unique_ptr<SDL_Texture, decltype(textureDeleter)> texture (
            SDL_CreateTextureFromSurface(renderer, surface.get()), textureDeleter);

        SDL_Rect dest_rect = {
            window_width - surface->w - MARGIN,  // Right-aligned with margin
            MARGIN,                              // Top margin
            surface->w,
            surface->h
        };

        SDL_RenderCopy(renderer, texture.get(), nullptr, &dest_rect);

        surface.reset(TTF_RenderText_Blended(
            font.get(),
            healthStr.c_str(),
            SDL_Color{255, 255, 255, 255}));

        texture.reset(SDL_CreateTextureFromSurface(renderer, surface.get()));

        dest_rect.x -= 200;

        SDL_RenderCopy(renderer, texture.get(), nullptr, &dest_rect);

        surface.reset(TTF_RenderText_Blended(
            font.get(),
            ultStr.c_str(),
            SDL_Color{255, 255, 255, 255}));

        texture.reset(SDL_CreateTextureFromSurface(renderer, surface.get()));

        dest_rect.x -= 200;

        SDL_RenderCopy(renderer, texture.get(), nullptr, &dest_rect);
    }
};

#endif //STATS_SYSTEM_HPP
