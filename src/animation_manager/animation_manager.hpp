#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include <map> // used for storing animations
#include <string> // used for storing texture, font

/**
 * @brief The AnimationData struct contains data for an animation.
 */
struct AnimationData {
    std::string texture_id; /**< The ID of the texture to use for the animation. */
    int width; /**< The width of each frame in the animation. */
    int height; /**< The height of each frame in the animation. */
    int num_frames; /**< The number of frames in the animation. */
    int frame_speed_rate;  /**< The speed rate of the animation. */
    bool is_loop;  /**< Whether the animation should loop. */

    /**
     * @brief Constructor for the AnimationData struct.
     * @param texture_id The ID of the texture to use for the animation.
     * @param width The width of each frame in the animation.
     * @param height The height of each frame in the animation.
     * @param num_frames The number of frames in the animation.
     * @param frame_speed_rate The speed rate of the animation.
     * @param is_loop Whether the animation should loop.
     */
    AnimationData(
        const std::string& texture_id = "",
        int width = 0,
        int height = 0,
        int num_frames = 1,
        int frame_speed_rate = 1,
        bool is_loop = true
    ) {
        this->texture_id = texture_id;
        this->width = width;
        this->height = height;
        this->num_frames = num_frames;
        this->frame_speed_rate = frame_speed_rate;
        this->is_loop = is_loop;
    }
};

/**
 * @brief The AnimationManager class is responsible for managing animations.
 */
class AnimationManager {
 private:
    std::map<std::string, AnimationData> animations; /**< Map of animations. */

 public:
    /**
     * @brief Constructor for the AnimationManager class.
     */
    AnimationManager();

    /**
     * @brief Destructor for the AnimationManager class.
     */
    ~AnimationManager();

    /**
     * @brief Clear all animations loaded by the AnimationManager.
     */
    void add_animation(
        const std::string& animation_id,
        const std::string& texture_id,
        int width,
        int height,
        int num_frames,
        int frame_speed_rate,
        bool is_loop
    );

    /**
     * @brief Get an animation from the AnimationManager.
     * @param animation_id The ID of the animation to get.
     * @return The AnimationData with the given ID.
     */
    AnimationData get_animation(const std::string& animation_id);
};

#endif  // ANIMATIONMANAGER_HPP