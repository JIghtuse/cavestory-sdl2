#include <string>
#include "animated_sprite.h"
#include "first_cave_bat.h"
#include "graphics.h"

const units::Frame kNumFlyFrames{3};
const units::FPS kFlyFps{10};
const std::string kSpritePath{"content/NpcCemet.bmp"};

FirstCaveBat::FirstCaveBat(Graphics& graphics, Vector<units::Game> pos) :
    pos_(pos),
    sprite_(std::shared_ptr<Sprite>(new AnimatedSprite{
                graphics,
                kSpritePath,
                units::tileToPixel(2), units::tileToPixel(3),
                units::tileToPixel(1), units::tileToPixel(1),
                kFlyFps, kNumFlyFrames
                }))
{}

FirstCaveBat::~FirstCaveBat() {}

void FirstCaveBat::draw(Graphics& graphics)
{
    sprite_->draw(graphics, pos_);
}

void FirstCaveBat::update(std::chrono::milliseconds elapsed_time) const
{
    sprite_->update(elapsed_time);
}
