#include "player.h"

const std::string kHealthSpriteFilePath{"TextBox"};
// HUD constants
const Vector<units::Game> kHealthBarPos{
    units::tileToGame(1),
    units::tileToGame(2)
};
const units::Game kHealthBarSourceX{0};
const units::Game kHealthBarSourceY{5 * units::kHalfTile};
const units::Game kHealthBarSourceWidth{units::tileToGame(4)};
const units::Game kHealthBarSourceHeight{units::kHalfTile};

const Vector<units::Game> kFillHealthBarPos{
    5 * units::kHalfTile,
    units::tileToGame(2)
};
const units::Game kFillMaxWidth{5 * units::kHalfTile - 2.0};
const units::Game kFillHealthBarSourceX{0};
const units::Game kFillHealthBarSourceY{3 * units::kHalfTile};
const units::Game kFillHealthBarSourceHeight{units::kHalfTile};

const Vector<units::Game> kDamageHealthPos{
    0,
    units::tileToGame(2)
};
const units::Game kDamageHealthSourceX{0};
const units::Game kDamageHealthSourceY{units::tileToGame(2)};
const units::Game kDamageHealthHeight{units::kHalfTile};

const Vector<units::Game> kHealthNumberPos{
    units::tileToGame(3) / 2,
    units::tileToGame(2)
};
const int kHealthNumDigits = 2;

const std::chrono::milliseconds kDamageDelay{1500};

Player::Health::Health(Graphics& graphics) :
    damage_{0},
    damage_timer_{kDamageDelay},
    max_health_{6},
    current_health_{6},
    health_bar_sprite_(
            graphics,
            kHealthSpriteFilePath,
            units::gameToPixel(kHealthBarSourceX),
            units::gameToPixel(kHealthBarSourceY),
            units::gameToPixel(kHealthBarSourceWidth),
            units::gameToPixel(kHealthBarSourceHeight)
            ),
    health_fill_bar_sprite_(
            graphics,
            kHealthSpriteFilePath,
            units::gameToPixel(kFillHealthBarSourceX),
            units::gameToPixel(kFillHealthBarSourceY),
            units::gameToPixel(kFillMaxWidth),
            units::gameToPixel(kFillHealthBarSourceHeight)
            ),
    damage_fill_sprite_(
            graphics,
            kHealthSpriteFilePath,
            units::gameToPixel(kDamageHealthSourceX),
            units::gameToPixel(kDamageHealthSourceY),
            units::gameToPixel(0),
            units::gameToPixel(kDamageHealthHeight)
            )
{}

void Player::Health::update()
{
    if (damage_ > 0 && damage_timer_.is_expired()) {
        current_health_ -= damage_;
        damage_ = 0;
    }
}

void Player::Health::draw(Graphics& graphics) const
{
    health_bar_sprite_.draw(graphics, kHealthBarPos);
    health_fill_bar_sprite_.draw(graphics, kFillHealthBarPos);

    if (damage_ > 0) {
        Vector<units::Game> pos{
            kFillHealthBarPos.x + fillOffset(current_health_ - damage_),
            kFillHealthBarPos.y
        };
        damage_fill_sprite_.draw(graphics, pos);
    }

    auto s = NumberSprite::HUDNumber(graphics, current_health_, kHealthNumDigits);
    s.draw(graphics, kHealthBarPos);
}

bool Player::Health::takeDamage(units::HP damage)
{
    damage_ = damage;
    damage_timer_.reset();

    const auto offset = fillOffset(current_health_ - damage);
    health_fill_bar_sprite_.set_width(units::gameToPixel(offset));
    damage_fill_sprite_.set_width(units::gameToPixel(fillOffset(damage)));

    return current_health_ <= 0;
}

units::Game Player::Health::fillOffset(units::HP health) const
{
    // TODO: fix drawing with negative health
    return kFillMaxWidth * health / max_health_;
}

