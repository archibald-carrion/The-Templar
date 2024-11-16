#include "controller_manager.hpp"
#include <iostream>

ControllerManager::ControllerManager() {
    //std::cout << "[CONTROLLERMANAGER] ControllerManager constructor" << std::endl;
}

ControllerManager::~ControllerManager() {
    //std::cout << "[CONTROLLERMANAGER] ControllerManager destructor" << std::endl;
}

void ControllerManager::add_key(const std::string& key_name, int key_code) {
    action_key_name.emplace(key_name, key_code);
    key_state.emplace(key_code, false);

}

void ControllerManager::update_key(const std::string& key_name, bool state) {
    // update the key state
    auto it = key_state.find(action_key_name[key_name]);
    // check if the key name exists
    if (it != key_state.end()) {
        key_state[action_key_name[key_name]] = state;
    }
}

void ControllerManager::update_key(int key_code, bool state) {
    // update the key state
    auto it = key_state.find(key_code);
    // check if the key code exists
    if (it != key_state.end()) {
        key_state[key_code] = state;
    }
}

void ControllerManager::set_key_to_pressed(const std::string& key_name) {
    // no need to check if the key name exists because it was checked in the previous function
    if (!key_name.empty()) {
        update_key(key_name, true);
    }
}

void ControllerManager::set_key_to_pressed(int key_code) {
    // no need to check if the key code exists because it was checked in the previous function
    if (key_code != -1) {
        update_key(key_code, true);
    }
}

void ControllerManager::set_key_to_up(const std::string& key_name) {
    // no need to check if the key name exists because it was checked in the previous function
    if (!key_name.empty()) {
        update_key(key_name, false);
    }
}

void ControllerManager::set_key_to_up(int key_code) {
    // no need to check if the key code exists because it was checked in the previous function
    if (key_code != -1) {
        update_key(key_code, false);
    }
}

bool ControllerManager::is_key_pressed(const std::string& key_name) {
    auto it = action_key_name.find(key_name);
    // check if the key name exists
    if (it != action_key_name.end()) {
        int key_code = action_key_name[key_name];
        return key_state[key_code];
    }
    return false;
}

void ControllerManager::clear() {
    action_key_name.clear();
    key_state.clear();
}

// MOUSE CONTROLLER

void ControllerManager::add_mouse_button(const std::string button_name, int mouse_button_code) {
    // print the button name and the mouse button code
    //std::cout << "[CONTROLLERMANAGER] Button name: " << button_name << " Mouse button code: " << mouse_button_code << std::endl;
    this->mouse_buttons_name.emplace(button_name, mouse_button_code);
    this->mouse_button_state.emplace(mouse_button_code, false);
}

bool ControllerManager::is_mouse_button_pressed(const std::string& button_name) {
    auto it = mouse_buttons_name.find(button_name);
    if(it != mouse_buttons_name.end()) {
        int button_code = mouse_buttons_name[button_name];
        return mouse_button_state[button_code];
    }
    return false;

}

void ControllerManager::update_mouse_button(int mouse_button_code, bool state) {
    auto it = mouse_button_state.find(mouse_button_code);
    if(it != mouse_button_state.end()) {
        mouse_button_state[mouse_button_code] = state;
    }
}

void ControllerManager::set_mouse_position(int x, int y) {
    mouse_position_x = x;
    mouse_position_y = y;
}

std::tuple<int, int> ControllerManager::get_mouse_position() {
    return {mouse_position_x, mouse_position_y};
}
    
void ControllerManager::set_mouse_button_to_pressed(int mouse_button_code) {
    update_mouse_button(mouse_button_code, true);
}

void ControllerManager::set_mouse_button_to_up(int mouse_button_code) {
    update_mouse_button(mouse_button_code, false);
}