#include <string>
#include "polar_star.h"
#include "sprite.h"

const std::string kArmsSpritePath{"content/Arms.bmp"};
const int kPolarStarIndex{2};
const units::Game kGunWidth{3 * units::kHalfTile};
const units::Game kGunHeight{2 * units::kHalfTile};

const units::Tile kHorizontalOffset{0};
const units::Tile kUpOffset{2};
const units::Tile kDownOffset{4};

const units::Tile kLeftOffset{0};
const units::Tile kRightOffset{1};

PolarStar::PolarStar(Graphics& graphics) :
    sprite_map_()
{
    initializeSprites(graphics);
}

PolarStar::~PolarStar() {}

void PolarStar::draw(
        Graphics& graphics,
        HorizontalFacing horizontal_facing, VerticalFacing vertical_facing,
        Vector<units::Game> pos) const
{
    if (horizontal_facing == HorizontalFacing::LEFT) {
        pos.x -= units::kHalfTile;
    }
    switch (vertical_facing) {
    case VerticalFacing::UP:
        pos.y -= units::kHalfTile / 2;
        break;
    case VerticalFacing::DOWN:
        pos.y += units::kHalfTile / 2;
        break;
    case VerticalFacing::HORIZONTAL:
    case VerticalFacing::LAST_VERTICAL_FACING:
        break;
    }
    const auto state = SpriteState{horizontal_facing, vertical_facing};
    sprite_map_.at(state)->draw(graphics, pos);
}

bool operator<(const PolarStar::SpriteState& a, const PolarStar::SpriteState& b)
{
    return std::tie(a.horizontal_facing, a.vertical_facing) <
            std::tie(b.horizontal_facing, b.vertical_facing);
}

void PolarStar::initializeSprites(Graphics& graphics)
{
    for (int h = (int)(HorizontalFacing::FIRST_HORIZONTAL_FACING);
            h < (int)(HorizontalFacing::LAST_HORIZONTAL_FACING);
            ++h) {
        for (int v = (int)(VerticalFacing::FIRST_VERTICAL_FACING);
                v < (int)(VerticalFacing::LAST_VERTICAL_FACING);
                ++v) {
            HorizontalFacing horiz_facing = (HorizontalFacing)h;
            VerticalFacing vert_facing = (VerticalFacing)v;
            initializeSprite(graphics, SpriteState(horiz_facing, vert_facing));
        }
    }
}

void PolarStar::initializeSprite(
        Graphics& graphics,
        const SpriteState& sprite_state)
{
    units::Tile tile_y;
    if (sprite_state.horizontal_facing == HorizontalFacing::LEFT) {
        tile_y = kLeftOffset;
    } else {
        tile_y = kRightOffset;
    }
    switch (sprite_state.vertical_facing) {
    case VerticalFacing::HORIZONTAL:
        tile_y += kHorizontalOffset;
        break;
    case VerticalFacing::UP:
        tile_y += kUpOffset;
        break;
    case VerticalFacing::DOWN:
        tile_y += kDownOffset;
        break;
    case VerticalFacing::LAST_VERTICAL_FACING:
        break;
    }
    sprite_map_[sprite_state] = std::shared_ptr<Sprite>{
        new Sprite(graphics,
            kArmsSpritePath,
            units::gameToPixel(kPolarStarIndex * kGunWidth),
            units::tileToPixel(tile_y),
            units::gameToPixel(kGunWidth),
            units::gameToPixel(kGunHeight)
            )
    };
}

