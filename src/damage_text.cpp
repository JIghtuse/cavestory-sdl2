#include <cmath>
#include "damage_text.h"
#include "number_sprite.h"

const units::Velocity kDamageTextVelocity{-units::kHalfTile / 250};
const std::chrono::milliseconds kDamageTime{2000};

DamageText::DamageText() :
    offset_y_{0},
    damage_{0},
    damage_timer_(kDamageTime),
    should_rise_{true}
{}

DamageText::~DamageText() {}

void DamageText::update(std::chrono::milliseconds elapsed_time)
{
    if (damage_timer_.is_expired()) {
        damage_ = 0;
    }
    if (should_rise_) {
        offset_y_ = std::max(-units::tileToGame(1),
                offset_y_ + kDamageTextVelocity * elapsed_time.count());
    }
}

void DamageText::draw(Graphics& graphics, Vector<units::Game> pos_center) const
{
    if (damage_timer_.is_expired()) {
        return;
    }
    pos_center.y += offset_y_;

    auto nsprite = NumberSprite::DamageNumber(graphics, damage_);
    nsprite.drawCentered(graphics, pos_center);
}

void DamageText::setDamage(units::HP damage)
{
    should_rise_ = (damage_ == 0);
    if (should_rise_) {
        offset_y_ = 0;
    }
    damage_ += damage;
    damage_timer_.reset();
}
