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

const int kRadix{10};

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
    reversed_glyphs_()
{
    assert(number >= 0 && "NumberSprite cannot show negative numbers!");

    const auto source_y = (color == ColorType::RED)
        ? kSourceRedY
        : kSourceWhiteY;
    int digit_count = 0;
    do {
        const int digit = number % kRadix;
        reversed_glyphs_.push_back(
                std::shared_ptr<Sprite>{new Sprite(
                    graphics,
                    kNumberSpritePath,
                    units::gameToPixel(digit * units::kHalfTile),
                    units::gameToPixel(source_y),
                    units::gameToPixel(kSourceWidth),
                    units::gameToPixel(kSourceHeight)
                    )});
        number /= kRadix;
        ++digit_count;
    } while (number != 0);
    assert((num_digits == 0 || num_digits >= digit_count)
            && "Wrong digits number");

    padding_ = (num_digits == 0)
        ? 0.0
        : units::kHalfTile * (num_digits - digit_count);

    switch(op) {
    case OperatorType::MINUS:
        reversed_glyphs_.push_back(
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
        reversed_glyphs_.push_back(
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

void NumberSprite::draw(Graphics& graphics, Vector<units::Game> pos) const
{
    for (size_t i = 0; i < reversed_glyphs_.size(); ++i) {
        const units::Game offset = units::kHalfTile *
            (reversed_glyphs_.size() - 1 - i);
        Vector<units::Game> digit_pos{pos.x + offset + padding_, pos.y};
        reversed_glyphs_[i]->draw(graphics, digit_pos);
    }
}

void NumberSprite::drawCentered(
        Graphics& graphics,
       Vector<units::Game> pos) const
{
    pos.x -= getWidth() / 2;
    pos.y -= getHeight() / 2;

    draw(graphics, pos);
}

units::Game NumberSprite::getWidth() const
{
    return units::kHalfTile * reversed_glyphs_.size();
}

units::Game NumberSprite::getHeight() const
{
    return units::kHalfTile;
}
