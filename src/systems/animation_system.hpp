#ifndef ANIMATION_SYSTEM_HPP
#define ANIMATION_SYSTEM_HPP

#include <SDL2/SDL.h> // SDL library for window creation and rendering

#include "../ECS/ECS.hpp" // Entity, System
#include "../components/animation_component.hpp" // AnimationComponent
#include "../components/sprite_component.hpp" // SpriteComponent

/***
 * @brief AnimationSystem class
 * The AnimationSystem class is a class for managing animations.
 */
class AnimationSystem : public System {
public:
    /***
     * @brief Constructor for AnimationSystem
     */
    AnimationSystem() {
        RequireComponent<AnimationComponent>();
        RequireComponent<SpriteComponent>();
    }

    /***
     * @brief Update the animation system, this will update the current frame of the animation component
     */
    void update() {
        for (auto entity : get_entities()) {
            auto& animation = entity.get_component<AnimationComponent>();
            auto& sprite = entity.get_component<SpriteComponent>();

            animation.current_frame = ((SDL_GetTicks() -animation.start_time) 
                * animation.frame_speed_rate / 1000) % animation.num_frames;
            sprite.src_rect.x = sprite.width * animation.current_frame;
        }
    }
};

#endif // ANIMATION_SYSTEM_HPP