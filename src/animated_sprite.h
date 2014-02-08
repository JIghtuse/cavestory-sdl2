#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "sprite.h"
#include "units.h"

struct AnimatedSprite : public Sprite {
    AnimatedSprite(
            Graphics& graphics,
            const std::string& file_path,
            int source_x, int source_y,
            int width, int height,
            units::FPS fps, int num_frames
            );

    ~AnimatedSprite();

    virtual void update(std::chrono::milliseconds elapsed_time);

private:
    std::chrono::milliseconds frame_time_;
    const int num_frames_;
    int current_frame_;
    std::chrono::milliseconds elapsed_time_; // since the last
                                             // frame change
};

#endif /*  ANIMATED_SPRITE_H */
