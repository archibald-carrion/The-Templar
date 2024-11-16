#ifndef ANIMATION_COMPONENT_HPP
#define ANIMATION_COMPONENT_HPP

#include <SDL2/SDL.h> // SDL library for window creation and rendering

/**
 * @struct AnimationComponent
 * @brief The AnimationComponent struct represents an animation component for an entity.
 */
struct AnimationComponent {
    int num_frames; // number of frames in the animation
    int current_frame; // current frame being displayed
    int frame_speed_rate; // speed rate of the animation
    bool is_loop; // flag to indicate if the animation is looping
    int start_time; // start time of the animation

    /**
     * @brief Construct a new Animation Component object
     * @param num_frames The number of frames in the animation
     * @param frame_speed_rate The speed rate of the animation
     * @param is_loop Flag to indicate if the animation is looping
     */
    AnimationComponent(int num_frames = 1, int frame_speed_rate = 1, bool is_loop = false) {
        this->num_frames = num_frames;
        this->frame_speed_rate = frame_speed_rate;
        this->is_loop = is_loop;
        this->current_frame = 1;
        this->start_time = SDL_GetTicks();
    }
};

#endif // ANIMATION_COMPONENT_HPP