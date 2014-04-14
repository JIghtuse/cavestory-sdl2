#include <string>
#include "animated_sprite.h"
#include "first_cave_bat.h"
#include "graphics.h"

const units::Frame kNumFlyFrames{3};
const units::FPS kFlyFps{13};
const units::AngularVelocity kAngularVelocity{120.0 / 1000.0};
const units::Game kFlightAmplitude{5 * units::kHalfTile};

const std::string kSpritePath{"NpcCemet"};

const units::HP kContactDamage{1};

FirstCaveBat::FirstCaveBat(Graphics& graphics, Vector<units::Game> pos) :
    pos_(pos),
    flight_center_y_{pos_.y},
    alive_{true},
    facing_{HorizontalFacing::RIGHT},
    flight_angle_{0.0},
    sprites_(),
    damage_text_(new DamageText())
{
    initializeSprites(graphics);
}

FirstCaveBat::~FirstCaveBat() {}

void FirstCaveBat::draw(Graphics& graphics) const
{
    sprites_.at(getSpriteState())->draw(graphics, pos_);
}

bool FirstCaveBat::update(const std::chrono::milliseconds elapsed_time,
        const units::Game player_x)
{
    flight_angle_ += kAngularVelocity * elapsed_time.count();

    facing_ = pos_.x + units::kHalfTile > player_x
        ? HorizontalFacing::LEFT
        : HorizontalFacing::RIGHT;

    const auto angle = std::sin(units::degreesToRadians(flight_angle_));
    pos_.y = flight_center_y_ + kFlightAmplitude * units::Game(angle);
    sprites_[getSpriteState()]->update();
    return alive_;
}

const Rectangle FirstCaveBat::getDamageRectangle() const
{
    return Rectangle(
            pos_.x + units::kHalfTile,
            pos_.y + units::kHalfTile,
            0,
            0);
}

const Rectangle FirstCaveBat::getCollisionRectangle() const
{
    return Rectangle( pos_.x,
            pos_.y,
            units::tileToGame(1),
            units::tileToGame(1)
            );
}

units::HP FirstCaveBat::contactDamage() const
{
    return kContactDamage;
}

void FirstCaveBat::takeDamage(units::HP damage)
{
    damage_text_->setDamage(damage);
    alive_ = false;
}

void FirstCaveBat::initializeSprites(Graphics& graphics)
{
    ENUM_FOREACH(facing, HorizontalFacing, HORIZONTAL_FACING) {
        initializeSprite(graphics, SpriteState(HorizontalFacing(facing)));
    }
}

void FirstCaveBat::initializeSprite(Graphics& graphics,
        const SpriteState& sprite_state)
{
    auto tile_y = sprite_state.facing == HorizontalFacing::RIGHT ? 3 : 2;
    sprites_[sprite_state] = std::shared_ptr<Sprite>(new AnimatedSprite{
            graphics,
            kSpritePath,
            units::tileToPixel(2), units::tileToPixel(tile_y),
            units::tileToPixel(1), units::tileToPixel(1),
            kFlyFps, kNumFlyFrames
            });
}

const FirstCaveBat::SpriteState FirstCaveBat::getSpriteState() const
{
    return SpriteState(facing_);
}

const Vector<units::Game> FirstCaveBat::getCenterPos() const
{
    return Vector<units::Game> {
        pos_.x + units::kHalfTile,
        pos_.y + units::kHalfTile
    };

}

const std::shared_ptr<DamageText> FirstCaveBat::getDamageText() const
{
    return damage_text_;
}
