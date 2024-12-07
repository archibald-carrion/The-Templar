#include "animation_manager.hpp"

AnimationManager::AnimationManager() {}

AnimationManager::~AnimationManager() {}

void AnimationManager::add_animation(
    const std::string& animation_id,
    const std::string& texture_id,
    int width,
    int height,
    int number_frames,
    int frame_speed_rate,
    bool is_loop) {
    
    auto animation_data = AnimationData(
        texture_id,
        width,
        height,
        number_frames,
        frame_speed_rate,
        is_loop);
    
    animations[animation_id] = animation_data;
}

AnimationData AnimationManager::get_animation(const std::string& animation_id) {
    return animations[animation_id];
}