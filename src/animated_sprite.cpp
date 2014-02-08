#include "animated_sprite.h"
#include "game.h"

AnimatedSprite::AnimatedSprite(
        Graphics& graphics,
        const std::string& file_path,
        const units::Pixel source_x, const units::Pixel source_y,
        const units::Pixel width, const units::Pixel height,
        const units::FPS fps, const units::Frame num_frames
        ) :
    Sprite(graphics, file_path, source_x, source_y, width, height),
    frame_time_(1000 / fps),
    num_frames_(num_frames),
    current_frame_(0),
    elapsed_time_()
{
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::update(std::chrono::milliseconds elapsed_time)
{
    elapsed_time_ += elapsed_time;
    if (elapsed_time_ > frame_time_) {
        ++current_frame_;
        elapsed_time_ = elapsed_time_.zero();
        if (current_frame_ < num_frames_) {
            source_rect_.x += source_rect_.w;
        } else {
            source_rect_.x -= source_rect_.w * (num_frames_ - 1);
            current_frame_ = 0;
        }
    }
}
