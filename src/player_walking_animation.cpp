#include "player.h"

// Walk Anumation
const units::Frame kNumWalkFrames{3};
const units::FPS kWalkFps{15};

Player::WalkingAnimation::WalkingAnimation() :
    frame_timer_{std::chrono::milliseconds{1000/kWalkFps}},
    current_index_{0},
    forward_{true}
{}

Player::StrideType Player::WalkingAnimation::stride() const
{
    switch (current_index_) {
    case 0:
        return StrideType::LEFT;
        break;
    case 1:
        return StrideType::MIDDLE;
        break;
    case 2:
        return StrideType::RIGHT;
        break;
    default:
        return StrideType::MIDDLE;
        break;
    }
    return StrideType::LEFT;
}

void Player::WalkingAnimation::reset() {
    forward_ = true;
    current_index_ = 0;
    frame_timer_.reset();
}

void Player::WalkingAnimation::update()
{
    if (frame_timer_.is_expired()) {
        frame_timer_.reset();
        if (forward_) {
            ++current_index_;
            forward_ = (current_index_ != kNumWalkFrames - 1);
        } else {
            --current_index_;
            forward_ = current_index_ == 0;
        }
    }
}
