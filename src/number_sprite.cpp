#include <cassert>
#include <string>
#include "number_sprite.h"
#include "sprite.h"

const std::string kNumberSpritePath{"content/TextBox.bmp"};
const units::Game kSourceY{7 * units::kHalfTile};
const units::Game kSourceHeight{units::kHalfTile};
const units::Game kSourceWidth{units::kHalfTile};

NumberSprite::NumberSprite(Graphics& graphics, int number, int num_digits) :
    padding_{0.0},
    reversed_digits_()
{
    assert(number >= 0);
    int digit_count = 0;
    do {
        const int digit = number % 10;
        reversed_digits_.push_back(
                std::shared_ptr<Sprite>{new Sprite(
                    graphics,
                    kNumberSpritePath,
                    units::gameToPixel(digit * units::kHalfTile),
                    units::gameToPixel(kSourceY),
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
}

NumberSprite::~NumberSprite() {}

void NumberSprite::draw(Graphics& graphics, Vector<units::Game> pos)
{
    for (size_t i = 0; i < reversed_digits_.size(); ++i) {
        const units::Game offset = units::kHalfTile *
            (reversed_digits_.size() - 1 - i);
        Vector<units::Game> digit_pos{pos.x + offset + padding_, pos.y};
        reversed_digits_[i]->draw(graphics, digit_pos);
    }
}
