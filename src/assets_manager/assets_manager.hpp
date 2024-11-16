#ifndef ASSETS_MANAGER_HPP
#define ASSETS_MANAGER_HPP

#include <SDL2/SDL.h> // SDL library for window creation and rendering
#include <SDL2/SDL_ttf.h> // SDL ttf library for rendering text

#include <map> // used for storing textures, fonts
#include <string> // used for storing texture, font

class AssetsManager {
private:
    std::map<std::string, SDL_Texture*> textures; /**< Map of textures. */
    std::map<std::string, TTF_Font*> fonts; /**< Map of fonts. */

public: 
    /**
     * @brief Constructor for the AssetsManager class.
     */
    AssetsManager();

    /**
     * @brief Destructor for the AssetsManager class.
     */
    ~AssetsManager();

    /**
     * @brief Clear all assets loaded by the AssetsManager.
     */
    void clear_assets();

    /**
     * @brief Add a texture to the AssetsManager.
     * @param renderer The SDL renderer to use for creating the texture.
     * @param texture_id The ID to use for the texture.
     * @param file_path The file path to the texture image.
     */
    void add_texture(
        SDL_Renderer* rendere,
        const std::string& texture_id,
        const std::string& file_path);

    /**
     * @brief Get a texture from the AssetsManager.
     * @param texture_id The ID of the texture to get.
     * @return The SDL texture with the given ID.
     */
    SDL_Texture* get_texture(const std::string& texture_id);

    /**
     * @brief Add a font to the AssetsManager.
     * @param font_id The ID to use for the font.
     * @param file_path The file path to the font file.
     * @param font_size The size of the font.
     */
    void add_font(const std::string& font_id, const std::string& file_path, int font_size);

    /**
     * @brief Get a font from the AssetsManager.
     * @param font_id The ID of the font to get.
     * @return The TTF font with the given ID.
     */
    TTF_Font* get_font(const std::string& font_id);
};


#endif // ASSETS_MANAGER_HPP