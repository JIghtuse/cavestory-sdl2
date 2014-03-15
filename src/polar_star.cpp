#include <string>
#include "polar_star.h"
#include "sprite.h"

const std::string kArmsSpritePath{"Arms"};
const int kPolarStarIndex{2};
const units::Game kGunWidth{3 * units::kHalfTile};
const units::Game kGunHeight{2 * units::kHalfTile};
const units::Game kGunBob{units::Game(2)};

const units::Tile kHorizontalOffset{0};
const units::Tile kUpOffset{2};
const units::Tile kDownOffset{4};

const units::Tile kLeftOffset{0};
const units::Tile kRightOffset{1};

// Nozzle Offsets
const units::Game kNozzleHorizontalY{23};
const units::Game kNozzleHorizontalLeftX{10};
const units::Game kNozzleHorizontalRightX{38};

const units::Game kNozzleUpY{4};
const units::Game kNozzleUpLeftX{27};
const units::Game kNozzleUpRightX{21};

const units::Game kNozzleDownY{28};
const units::Game kNozzleDownLeftX{29};
const units::Game kNozzleDownRightX{19};

// Projectile Sprite
const units::Tile kProjectileSourceY{2};
const units::Tile kHorizontalProjectileSourceX{8};
const units::Tile kVerticalProjectileSourceX{9};
const units::Tile kProjectileWidth{1};
const units::Tile kProjectileHeight{1};
// Projectile Velocity
const units::Velocity kProjectileSpeed{0.6};

const units::Game kProjectileMaxOffset{7 * units::kHalfTile};

PolarStar::PolarStar(Graphics& graphics) :
    sprite_map_(),
    horizontal_projectile_(),
    vertical_projectile_(),
    projectile_()
{
    initializeSprites(graphics);
}

PolarStar::~PolarStar() {}

void PolarStar::updateProjectiles(std::chrono::milliseconds elapsed_time)
{
    if (projectile_) {
        if (!projectile_->update(elapsed_time)) {
            projectile_.reset();
        }
    }
}

void PolarStar::draw(
        Graphics& graphics,
        const HorizontalFacing hfacing,
        const VerticalFacing vfacing,
        bool gun_up,
        Vector<units::Game> player_pos) const
{
    const auto gun_pos = calcGunPos(player_pos, hfacing, vfacing, gun_up);
    const auto state = SpriteState{hfacing, vfacing};
    sprite_map_.at(state)->draw(graphics, gun_pos);

    if (projectile_ != nullptr) {
        projectile_->draw(graphics);
    }
}

void PolarStar::startFire(
        const Vector<units::Game> player_pos,
        const HorizontalFacing hfacing,
        const VerticalFacing vfacing,
        bool gun_up
        )
{
    const auto gun_pos = calcGunPos(player_pos, hfacing, vfacing, gun_up);
    const auto bullet_pos = getBulletPos(gun_pos, hfacing, vfacing);
    projectile_.reset(new Projectile(
                (vfacing == VerticalFacing::HORIZONTAL)
                ? horizontal_projectile_ : vertical_projectile_,
                hfacing,
                vfacing,
                bullet_pos
                ));

}

void PolarStar::stopFire() {}

PolarStar::Projectile::Projectile(std::shared_ptr<Sprite> sprite,
        const HorizontalFacing hdirection,
        const VerticalFacing vdirection,
        const Vector<units::Game> pos) :
    pos_(pos),
    horizontal_direction_(hdirection),
    vertical_direction_(vdirection),
    sprite_(sprite),
    offset_(0)
{}

bool PolarStar::Projectile::update(std::chrono::milliseconds elapsed_time)
{
    offset_ += kProjectileSpeed * elapsed_time.count();
    return offset_ < kProjectileMaxOffset;
}

void PolarStar::Projectile::draw(Graphics& graphics) const
{
    auto pos = Vector<units::Game>{ pos_.x, pos_.y };
    switch (vertical_direction_) {
    case VerticalFacing::HORIZONTAL:
        pos.x += (horizontal_direction_ == HorizontalFacing::LEFT)
            ? -offset_
            : offset_;
        break;
    case VerticalFacing::UP:
        pos.y -= offset_;
        break;
    case VerticalFacing::DOWN:
        pos.y += offset_;
        break;
    default: break;
    }
    sprite_->draw(graphics, pos);
}

bool operator<(const PolarStar::SpriteState& a, const PolarStar::SpriteState& b)
{
    return std::tie(a.horizontal_facing, a.vertical_facing) <
        std::tie(b.horizontal_facing, b.vertical_facing);
}

const Vector<units::Game> PolarStar::calcGunPos(
        const Vector<units::Game> player_pos,
        const HorizontalFacing hfacing,
        const VerticalFacing vfacing,
        const bool gun_up
        ) const
{
    Vector<units::Game> pos(player_pos);
    if (hfacing == HorizontalFacing::LEFT) {
        pos.x -= units::kHalfTile;
    }
    switch (vfacing) {
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
    if (gun_up) {
        pos.y -= kGunBob;
    }
    return pos;
}

const Vector<units::Game> PolarStar::getBulletPos(
        const Vector<units::Game> player_pos,
        const HorizontalFacing hfacing,
        const VerticalFacing vfacing
        ) const
{
    auto bullet_x = player_pos.x - units::kHalfTile;
    auto bullet_y = player_pos.y - units::kHalfTile;

    switch (vfacing) {
        case VerticalFacing::HORIZONTAL:
            bullet_y += kNozzleHorizontalY;

            switch (hfacing) {
                case HorizontalFacing::LEFT:
                    bullet_x += kNozzleHorizontalLeftX;
                    break;
                case HorizontalFacing::RIGHT:
                    bullet_x += kNozzleHorizontalRightX;
                    break;
                default:
                    break;
            }

            break;
        case VerticalFacing::UP:
            bullet_y += kNozzleUpY;

            switch (hfacing) {
                case HorizontalFacing::LEFT:
                    bullet_x += kNozzleUpLeftX;
                    break;
                case HorizontalFacing::RIGHT:
                    bullet_x += kNozzleUpRightX;
                    break;
                default:
                    break;
            }

            break;
        case VerticalFacing::DOWN:
            bullet_y += kNozzleDownY;

            switch (hfacing) {
                case HorizontalFacing::LEFT:
                    bullet_x += kNozzleDownLeftX;
                    break;
                case HorizontalFacing::RIGHT:
                    bullet_x += kNozzleDownRightX;
                    break;
                default:
                    break;
            }

            break;
        default:
            break;
    }

    return Vector<units::Game>{bullet_x, bullet_y};
}

void PolarStar::initializeSprites(Graphics& graphics)
{
    horizontal_projectile_.reset(new Sprite(
                graphics, "Bullet",
                units::tileToPixel(kHorizontalProjectileSourceX),
                units::tileToPixel(kProjectileSourceY),
                units::tileToPixel(kProjectileWidth),
                units::tileToPixel(kProjectileHeight)
                ));
    vertical_projectile_.reset(new Sprite(
                graphics, "Bullet",
                units::tileToPixel(kVerticalProjectileSourceX),
                units::tileToPixel(kProjectileSourceY),
                units::tileToPixel(kProjectileWidth),
                units::tileToPixel(kProjectileHeight)
                ));
    ENUM_FOREACH(h, HorizontalFacing, HORIZONTAL_FACING) {
        ENUM_FOREACH(v, VerticalFacing, VERTICAL_FACING) {
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

