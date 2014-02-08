#include "animated_sprite.h"
#include "game.h"

AnimatedSprite::AnimatedSprite(
        Graphics& graphics,
        const std::string& file_path,
        units::Pixel source_x, units::Pixel source_y,
        units::Pixel width, units::Pixel height,
        units::FPS fps, units::Frame num_frames
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
        current_frame_ = (current_frame_ + 1) % num_frames_;
        source_rect_.x = source_rect_.w * current_frame_;

        elapsed_time_ = elapsed_time_.zero();
    }
}
