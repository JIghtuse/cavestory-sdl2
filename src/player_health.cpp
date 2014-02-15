#include "player.h"

const std::string kHealthSpriteFilePath{"content/TextBox.bmp"};
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
const units::Game kFillHealthBarSourceX{0};
const units::Game kFillHealthBarSourceY{3 * units::kHalfTile};
const units::Game kFillHealthBarSourceHeight{units::kHalfTile};

const Vector<units::Game> kHealthNumberPos{
    units::tileToGame(3) / 2,
    units::tileToGame(2)
};
const int kHealthNumDigits = 2;

const std::chrono::milliseconds kDamageDelay{1500};

Player::Health::Health(Graphics& graphics) :
    damage_{0},
    damage_time_{0},
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
                units::gameToPixel(5 * units::kHalfTile - 2.0),
                units::gameToPixel(kFillHealthBarSourceHeight)
                )
{
   ;
}

void Player::Health::update(std::chrono::milliseconds elapsed_time)
{
    if (damage_ > 0) {
        damage_time_ += elapsed_time;
        if (damage_time_ > kDamageDelay) {
            current_health_ -= damage_;
            damage_ = 0;
        }
    }
}

void Player::Health::draw(Graphics& graphics) const
{
    health_bar_sprite_.draw(graphics, kHealthBarPos);
    health_fill_bar_sprite_.draw(graphics, kFillHealthBarPos);

    auto s = NumberSprite(graphics, current_health_, kHealthNumDigits);
    s.draw(graphics, kHealthBarPos);
}

bool Player::Health::takeDamage(units::HP damage)
{
    damage_ = damage;
    damage_time_ = damage_time_.zero();

    return current_health_ <= 0;
}

