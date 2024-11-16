#include "animation_manager.hpp"

AnimationManager::AnimationManager() {}
AnimationManager::~AnimationManager() {}

void AnimationManager::add_animation(const std::string& animationId,
    const std::string& textureId, int width, int height, int numFrames
    , int frameSpeedRate, bool isLoop) {
    
    auto animData = AnimationData(textureId, width, height, numFrames
        , frameSpeedRate, isLoop);
    
    animations[animationId] = animData;
}

AnimationData AnimationManager::get_animation(const std::string& animationId) {
    return animations[animationId];
}