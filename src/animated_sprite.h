#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "sprite.h"
#include "units.h"

struct AnimatedSprite : public Sprite {
    AnimatedSprite(
            Graphics& graphics,
            const std::string& file_path,
            const units::Pixel source_x, const units::Pixel source_y,
            const units::Pixel width, const units::Pixel height,
            const units::FPS fps, const units::Frame num_frames
            );

    ~AnimatedSprite();

    void update(const std::chrono::milliseconds elapsed_time);

private:
    const std::chrono::milliseconds frame_time_;
    const units::Frame num_frames_;
    units::Frame current_frame_;
    std::chrono::milliseconds elapsed_time_; // since the last
                                             // frame change
};

#endif /*  ANIMATED_SPRITE_H */
