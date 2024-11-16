#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <map> // std::map
#include <sol/sol.hpp> // Lua scripting
#include <string> // std::string

#include "scene_loader.hpp" // SceneLoader

/**
 * @class SceneManager
 * @brief The SceneManager class is a class for managing scenes.
 */
class SceneManager {
private:
    std::map<std::string, std::string> scenes; // scenes
    std::string next_scene; // next scene
    bool is_scene_running = false; // flag to indicate if the scene is running
    std::unique_ptr<SceneLoader> scene_loader; // scene loader

public:
    /**
     * @brief Construct a new SceneManager object
     */
    SceneManager();

    /**
     * @brief Destroy the SceneManager object
     */
    ~SceneManager();

    /**
     * @brief Load a scene from a script
     * @param scene_path The path to the scene script
     * @param lua The Lua state
     */
    void load_scene_from_script(const std::string& scene_path, sol::state& lua);

    /**
     * @brief Load a scene
     */
    void load_scene();

    /**
     * @brief Get the next scene
     * @return The next scene
     */
    std::string get_next_scene() const;

    /**
     * @brief Set the next scene
     * @param next_scene The next scene
     */
    void set_next_scene(const std::string& next_scene);

    /**
     * @brief Check if the current scene is running
     * @return true if the current scene is running, false otherwise
     */
    bool is_current_scene_running() const;

    /**
     * @brief Start the scene
     */
    void start_scene();

    /**
     * @brief Stop the scene
     */
    void stop_scene();

};

#endif // SCENE_MANAGER_HPP