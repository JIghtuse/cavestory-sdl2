#include <string>
#include "animated_sprite.h"
#include "first_cave_bat.h"
#include "graphics.h"

const units::Frame kNumFlyFrames{3};
const units::FPS kFlyFps{13};
const units::AngularVelocity kAngularVelocity{120.0 / 1000.0};
const units::Game kMoveAmplitude{units::tileToGame(5) / 2.0};

const std::string kSpritePath{"content/NpcCemet.bmp"};

FirstCaveBat::FirstCaveBat(Graphics& graphics, Vector<units::Game> pos) :
    pos_(pos),
    flight_angle_(0.0),
    sprite_(std::shared_ptr<Sprite>(new AnimatedSprite{
                graphics,
                kSpritePath,
                units::tileToPixel(2), units::tileToPixel(3),
                units::tileToPixel(1), units::tileToPixel(1),
                kFlyFps, kNumFlyFrames
                }))
{}

FirstCaveBat::~FirstCaveBat() {}

void FirstCaveBat::draw(Graphics& graphics) const
{
    const auto angle = std::sin(units::degreesToRadians(flight_angle_));
    const auto y = pos_.y + kMoveAmplitude * angle;
    auto current_pos = Vector<units::Game> { pos_.x, y };
    sprite_->draw(graphics, current_pos);
}

void FirstCaveBat::update(std::chrono::milliseconds elapsed_time)
{
    flight_angle_ += kAngularVelocity * elapsed_time.count();
    sprite_->update(elapsed_time);
}
