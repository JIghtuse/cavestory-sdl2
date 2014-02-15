#include <cassert>
#include <string>
#include "number_sprite.h"
#include "sprite.h"

const std::string kNumberSpritePath{"content/TextBox.bmp"};
const units::Game kSourceWhiteY{7 * units::kHalfTile};
const units::Game kSourceRedY{8 * units::kHalfTile};

const units::Game kOpSourceY{6 * units::kHalfTile};
const units::Game kPlusSourceX{4 * units::kHalfTile};
const units::Game kMinusSourceX{5 * units::kHalfTile};

const units::Game kSourceHeight{units::kHalfTile};
const units::Game kSourceWidth{units::kHalfTile};

NumberSprite NumberSprite::HUDNumber(Graphics& graphics,
        int number,
        int num_digits)
{
    return NumberSprite(
            graphics,
            number,
            num_digits,
            ColorType::WHITE,
            OperatorType::NONE);
}

NumberSprite NumberSprite::DamageNumber(Graphics& graphics, int number)
{
    return NumberSprite(
            graphics,
            number,
            0,
            ColorType::RED,
            OperatorType::MINUS);
}

NumberSprite NumberSprite::ExperienceNumber(Graphics& graphics, int number)
{
    return NumberSprite(
            graphics,
            number,
            0,
            ColorType::WHITE,
            OperatorType::PLUS);
}

NumberSprite::NumberSprite(Graphics& graphics,
        int number,
        int num_digits,
        ColorType color,
        OperatorType op
        ) :
    op_(op),
    padding_{0.0},
    reversed_sprites_()
{
    assert(number >= 0);

    const auto source_y = (color == ColorType::RED)
        ? kSourceRedY
        : kSourceWhiteY;
    int digit_count = 0;
    do {
        const int digit = number % 10;
        reversed_sprites_.push_back(
                std::shared_ptr<Sprite>{new Sprite(
                    graphics,
                    kNumberSpritePath,
                    units::gameToPixel(digit * units::kHalfTile),
                    units::gameToPixel(source_y),
                    units::gameToPixel(kSourceWidth),
                    units::gameToPixel(kSourceHeight)
                    )});
        number /= 10;
        ++digit_count;
    } while (number != 0);
    assert(num_digits == 0 || num_digits >= digit_count);

    padding_ = (num_digits == 0)
        ? 0.0
        : units::kHalfTile * (num_digits - digit_count);

    switch(op) {
    case OperatorType::MINUS:
        reversed_sprites_.push_back(
                std::shared_ptr<Sprite>{new Sprite(
                    graphics,
                    kNumberSpritePath,
                    units::gameToPixel(kMinusSourceX),
                    units::gameToPixel(kOpSourceY),
                    units::gameToPixel(kSourceWidth),
                    units::gameToPixel(kSourceHeight)
                    )});
        break;
    case OperatorType::PLUS:
        reversed_sprites_.push_back(
                std::shared_ptr<Sprite>{new Sprite(
                    graphics,
                    kNumberSpritePath,
                    units::gameToPixel(kPlusSourceX),
                    units::gameToPixel(kOpSourceY),
                    units::gameToPixel(kSourceWidth),
                    units::gameToPixel(kSourceHeight)
                    )});
        break;
    case OperatorType::NONE:
        break;
    }
}

NumberSprite::~NumberSprite() {}

void NumberSprite::draw(Graphics& graphics, Vector<units::Game> pos)
{
    for (size_t i = 0; i < reversed_sprites_.size(); ++i) {
        const units::Game offset = units::kHalfTile *
            (reversed_sprites_.size() - 1 - i);
        Vector<units::Game> digit_pos{pos.x + offset + padding_, pos.y};
        reversed_sprites_[i]->draw(graphics, digit_pos);
    }
}

units::Game NumberSprite::getWidth() const
{
    return units::kHalfTile * reversed_sprites_.size();
}

units::Game NumberSprite::getHeight() const
{
    return units::kHalfTile;
}
