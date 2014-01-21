#include "animated_sprite.h"
#include "game.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(const std::string& file_path,
            int source_x, int source_y,
            int width, int height,
            SDL_Renderer* ren,
            int fps, int num_frames) :
    Sprite(file_path, source_x, source_y, width, height, ren),
    frame_time_(1000 / fps),
    num_frames_(num_frames),
    current_frame_(0),
    elapsed_time_()
{
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::update(
        std::chrono::duration<double,std::milli> elapsed_time)
{
    elapsed_time_ += elapsed_time;
    if (elapsed_time_ > frame_time_) {
        current_frame_ = (current_frame_ + 1) % num_frames_;
        source_rect_.x = Game::kTileSize * current_frame_;

        elapsed_time_ = elapsed_time_.zero();
    }
}
