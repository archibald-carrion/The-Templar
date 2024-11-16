#ifndef TEXT_COMPONENT_HPP
#define TEXT_COMPONENT_HPP

#include <SDL2/SDL.h> // SDL library for window creation and rendering, used for SDL_Color
#include <string> // std::string

/**
 * @struct TextComponent
 * @brief The TextComponent struct represents a text component for an entity.
 */
struct TextComponent {
    std::string text; // text to display
    std::string font_id; // font id of the text
    SDL_Color color; // color of the text
    int width; // width of the text
    int height; // height of the text

    /**
     * @brief Construct a new Text Component object
     * @param text The text to display
     * @param font_id The font id of the text
     * @param r The red color value
     * @param g The green color value
     * @param b The blue color value
     * @param a The alpha color value
     */
    TextComponent(const std::string& text = "", const std::string& font_id = "", u_char r = 0, u_char g = 0, u_char b = 0,u_char a = 0) {
        this->text = text;
        this->font_id = font_id;
        this->color.r = r;
        this->color.g = g;
        this->color.b = b;
        this->color.a = a;
        this->width = 0;
        this->height = 0;
    }
};

#endif // TEXT_COMPONENT_HPP