#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "sprite.h"
#include "units.h"

struct AnimatedSprite : public Sprite {
    AnimatedSprite(
            Graphics& graphics,
            const std::string& file_path,
            units::Pixel source_x, units::Pixel source_y,
            units::Pixel width, units::Pixel height,
            units::FPS fps, units::Frame num_frames
            );

    ~AnimatedSprite();

    virtual void update(std::chrono::milliseconds elapsed_time);

private:
    std::chrono::milliseconds frame_time_;
    const units::Frame num_frames_;
    units::Frame current_frame_;
    std::chrono::milliseconds elapsed_time_; // since the last
                                             // frame change
};

#endif /*  ANIMATED_SPRITE_H */
