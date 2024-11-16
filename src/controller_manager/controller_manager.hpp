#ifndef CONTROLLER_MANAGER_HPP
#define CONTROLLER_MANAGER_HPP

#include<SDL2/SDL.h> // SDL library for window creation and rendering
#include <map> // std::map
#include <tuple> // std::tuple
#include <string> // std::string

/**
 * @class ControllerManager
 * @brief The ControllerManager class manages the user input from the keyboard and mouse.
 */
class ControllerManager {
private:
    std::map<std::string, int> action_key_name; // map of action key names to key codes
    std::map<int, bool> key_state; // map of key codes to key states (pressed or not pressed)

    std::map<std::string, int> mouse_buttons_name; // map of mouse button names to mouse button codes
    std::map<int, bool> mouse_button_state; // map of mouse button codes to mouse button states (pressed or not pressed)
    
    int mouse_position_x; // x position of the mouse
    int mouse_position_y; // y position of the mouse

public:
    /**
     * @brief Construct a new Controller Manager object
     */
    ControllerManager();

    /**
     * @brief Destroy the Controller Manager object
     */
    ~ControllerManager();

    /**
     * @brief Clear all the key states
     */
    void clear();

    /**
     * @brief Add a key to the controller manager
     * @param key_name The name of the key
     * @param key_code The key code
     */
    void add_key(const std::string& key_name, int key_code);

    /**
     * @brief Check if a key is pressed
     * @param key_name The name of the key
     * @return true if the key is pressed, false otherwise
     */
    bool is_key_pressed(const std::string& key_name);

    /**
     * @brief Update the key state
     * @param key_name The name of the key
     * @param state The state of the key
     */
    void update_key(const std::string& key_name, bool state);

    /**
     * @brief Update the key state
     * @param key_code The key code
     * @param state The state of the key
     */
    void update_key(int key_code, bool state);

    /**
     * @brief Set the mouse position
     * @param x The x position of the mouse
     * @param y The y position of the mouse
     */
    void set_key_to_pressed(int key_code);

    /**
     * @brief Set the key to pressed
     * @param key_name The name of the key
     */
    void set_key_to_pressed(const std::string& key_name);

    /**
     * @brief Set the key to up
     * @param key_code The key code
     */
    void set_key_to_up(int key_code);

    /**
     * @brief Set the key to up
     * @param key_name The name of the key
     */
    void set_key_to_up(const std::string& key_name);

    /**
     * @brief Add a mouse button to the controller manager
     * @param button_name The name of the mouse button
     * @param mouse_button_code The mouse button code
     */
    void add_mouse_button(const std::string button_name, int mouse_button_code);

    /**
     * @brief Check if a mouse button is pressed
     * @param mouse_button_name The name of the mouse button
     * @return true if the mouse button is pressed, false otherwise
     */
    bool is_mouse_button_pressed(const std::string& mouse_button_name);

    /**
     * @brief Update the mouse button state
     * @param mouse_button_name The name of the mouse button
     * @param state The state of the mouse button
     */
    void update_mouse_button(int mouse_button_code, bool state);

    /**
     * @brief Update the mouse button state
     * @param mouse_button_code The mouse button code
     * @param state The state of the mouse button
     */
    void set_mouse_position(int x, int y);

    /**
     * @brief Get the mouse position
     * @return std::tuple<int, int> The x and y position of the mouse
     */
    std::tuple<int, int> get_mouse_position();
    
    /**
     * @brief Set the mouse button to pressed
     * @param mouse_button_code The mouse button code
     */
    void set_mouse_button_to_pressed(int mouse_button_code);

    /**
     * @brief Set the mouse button to up
     * @param mouse_button_code The mouse button code
     */
    void set_mouse_button_to_up(int mouse_button_code);
};

#endif // CONTROLLER_MANAGER_HPP