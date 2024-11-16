#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include <map>
#include <string>

struct AnimationData {
    std::string texture_id;
    int width;
    int height;
    int num_frames;
    int frame_speed_rate;
    bool is_loop;

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

class AnimationManager {
private:
    std::map<std::string, AnimationData> animations;

public:
    AnimationManager();
    ~AnimationManager();

    void add_animation(
        const std::string& animation_id,
        const std::string& texture_id,
        int width,
        int height,
        int num_frames,
        int frame_speed_rate,
        bool is_loop
    );

    AnimationData get_animation(const std::string& animation_id);
};

#endif  // ANIMATIONMANAGER_HPP