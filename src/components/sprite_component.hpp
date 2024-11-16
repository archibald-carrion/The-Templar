#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SDL2/SDL.h> // SDL library for window creation and rendering, used for SDL_Rect
#include <string> // std::string

/**
 * @struct SpriteComponent
 * @brief The SpriteComponent struct represents a sprite for an entity.
 */
struct SpriteComponent {
    std::string texture_id; // texture id of the sprite
    int height; // height of the sprite
    int width; // width of the sprite
    SDL_Rect src_rect; // source rectangle of the sprite
    bool flip = false; // flip the sprite

    /**
     * @brief Construct a new Sprite Component object
     * @param texture_id The texture id of the sprite
     * @param width The width of the sprite
     * @param height The height of the sprite
     * @param src_rect_X The x coordinate of the source rectangle
     * @param src_rect_Y The y coordinate of the source rectangle
     */
    SpriteComponent(const std::string& texture_id = "none", int width = 0, int height = 0, int src_rect_X =0, int src_rect_Y = 0) {
        this->texture_id = texture_id;
        this->height = height;
        this->width = width;
        this->src_rect = {src_rect_X, src_rect_Y, width, height};
    }
};

#endif // SPRITE_COMPONENT_HPP