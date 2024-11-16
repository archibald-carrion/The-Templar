#ifndef SCENE_LOADER_HPP
#define SCENE_LOADER_HPP

#include <memory> // used for smart pointers
#include <string> // used for file paths
#include <SDL2/SDL.h> // SDL library for window creation and rendering
#include <sol/sol.hpp> // Lua scripting
#include<tinyxml2/tinyxml2.h> 

#include "../animation_manager/animation_manager.hpp" // Animation manager for handling animations
#include "../audio_manager/audio_manager.hpp" // Audio manager for handling audio
#include "../assets_manager/assets_manager.hpp" // Assets manager for loading textures and fonts 
#include "../controller_manager/controller_manager.hpp" // Controller manager for handling user input
#include "../ECS/ECS.hpp" // ECS library for entity-component-system

class SceneLoader {
private:
    
    /**
     * @brief Load the sounds from the Lua table.
     * @param sounds The Lua table containing the sounds.
     * @param audio_manager The audio manager to load the sounds into.
     */
    void load_sounds(const sol::table& sounds, std::unique_ptr<AudioManager>& audio_manager);

    /**
     * @brief Load the music from the Lua table.
     * @param music The Lua table containing the music.
     * @param audio_manager The audio manager to load the music into.
     */
    void load_music(const sol::table& music, std::unique_ptr<AudioManager>& audio_manager);
    
    /**
     * @brief Load the sprites from the Lua table.
     * @param renderer The SDL renderer to use for creating the textures.
     * @param sprites The Lua table containing the sprites.
     * @param asset_manager The assets manager to load the sprites into.
     */
    void load_sprites(SDL_Renderer* renderer, const sol::table& sprites, std::unique_ptr<AssetsManager>& asset_manager);

    /**
     * @brief Load the fonts from the Lua table.
     * @param fonts The Lua table containing the fonts.
     * @param asset_manager The assets manager to load the fonts into.
     */
    void load_fonts(const sol::table& fonts, std::unique_ptr<AssetsManager>& asset_manager);
    
    /**
     * @brief Load the buttons from the Lua table.
     * @param buttons The Lua table containing the buttons.
     * @param controller_manager The controller manager to load the buttons into.
     */
    void load_buttons(const sol::table& buttons, std::unique_ptr<ControllerManager>& controller_manager);

    /**
     * @brief Load the keys from the Lua table.
     * @param keys The Lua table containing the keys.
     * @param controller_manager The controller manager to load the keys into.
     */
    void load_keys_actions(const sol::table& keys, std::unique_ptr<ControllerManager>& controller_manager);

    /**
     * @brief Load the entities from the Lua table.
     * @param lua The Lua state to use for creating the entities.
     * @param entities The Lua table containing the entities.
     * @param registry The registry to load the entities into.
     */
    void load_entities(sol::state& lua, const sol::table& entities, std::unique_ptr<Registry>& registry);

    void load_animations(const sol::table& animations, std::unique_ptr<AnimationManager>& animation_manager);

    void LoadMap(const sol::table map, std::unique_ptr<Registry> &registry);
    void LoadLayer(std::unique_ptr<Registry> &registry, tinyxml2::XMLElement *layerElement, int tWidth, int tHeight, int mWidth, const std::string &tileSet, int columns);
    void LoadColliders(std::unique_ptr<Registry> &registry, tinyxml2::XMLElement *objectGroup);
public:
    /**
     * @brief Default constructor for the SceneLoader class.
     */
    SceneLoader();

    /**
     * @brief Destructor for the SceneLoader class.
     */
    ~SceneLoader();

    /**
     * @brief Load a scene from a Lua script.
     * @param scene_path The file path to the Lua script.
     * @param lua The Lua state to use for loading the scene.
     * @param asset_manager The assets manager to load the assets into.
     * @param controller_manager The controller manager to load the controllers into.
     * @param audio_manager The audio manager to load the audio into.
     * @param registry The registry to load the entities into.
     * @param renderer The SDL renderer to use for creating the textures.
     */
    void load_scene(const std::string& scene_path,
        sol::state& lua, 
        std::unique_ptr<AssetsManager>& asset_manager, 
        std::unique_ptr<ControllerManager>& controller_manager,
        std::unique_ptr<AudioManager>& audio_manager,
        std::unique_ptr<Registry>& registry, 
        std::unique_ptr<AnimationManager>& animation_manager,
        SDL_Renderer* renderer);
};

#endif // SCENE_LOADER_HPP