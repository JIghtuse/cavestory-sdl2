#include <string>
#include "map.h"
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
const units::Tile kProjectileSourceWidth{1};
const units::Tile kProjectileSourceHeight{1};
// Projectile Velocity
const units::Velocity kProjectileSpeed{0.6};

const units::Game kProjectileMaxOffset{7 * units::kHalfTile};
const units::Game kProjectileWidth{4.0};

PolarStar::PolarStar(Graphics& graphics) :
    sprite_map_(),
    horizontal_projectile_(),
    vertical_projectile_(),
    projectile_a_(),
    projectile_b_()
{
    initializeSprites(graphics);
}

PolarStar::~PolarStar() {}

void PolarStar::updateProjectiles(std::chrono::milliseconds elapsed_time,
        const Map& map)
{
    if (projectile_a_) {
        if (!projectile_a_->update(elapsed_time, map)) {
            projectile_a_.reset();
        }
    }
    if (projectile_b_) {
        if (!projectile_b_->update(elapsed_time, map)) {
            projectile_b_.reset();
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

    if (projectile_a_ != nullptr) {
        projectile_a_->draw(graphics);
    }
    if (projectile_b_ != nullptr) {
        projectile_b_->draw(graphics);
    }
}

void PolarStar::startFire(
        const Vector<units::Game> player_pos,
        const HorizontalFacing hfacing,
        const VerticalFacing vfacing,
        bool gun_up
        )
{
    if (projectile_a_ != nullptr && projectile_b_ != nullptr) {
        return;
    }
    const auto gun_pos = calcGunPos(player_pos, hfacing, vfacing, gun_up);
    const auto bullet_pos = getBulletPos(gun_pos, hfacing, vfacing);
    if (projectile_a_ == nullptr) {
        projectile_a_.reset(new Projectile(
                    (vfacing == VerticalFacing::HORIZONTAL)
                    ? horizontal_projectile_ : vertical_projectile_,
                    hfacing,
                    vfacing,
                    bullet_pos
                    ));
    } else if (projectile_b_ == nullptr) {
        projectile_b_.reset(new Projectile(
                    (vfacing == VerticalFacing::HORIZONTAL)
                    ? horizontal_projectile_ : vertical_projectile_,
                    hfacing,
                    vfacing,
                    bullet_pos
                    ));
    }
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

bool PolarStar::Projectile::update(std::chrono::milliseconds elapsed_time,
        const Map &map)
{
    offset_ += kProjectileSpeed * elapsed_time.count();

    const std::vector<Map::CollisionTile> colliding_tiles{
        map.getCollidingTiles(getCollisionRectangle())
    };

    for (auto &tile : colliding_tiles) {
        if (tile.tile_type == Map::TileType::WALL) {
            return false;
        }
    }
    return offset_ < kProjectileMaxOffset;
}

void PolarStar::Projectile::draw(Graphics& graphics) const
{
    sprite_->draw(graphics, getPos());
}

Rectangle PolarStar::Projectile::getCollisionRectangle() const
{
    const auto width = (vertical_direction_ == VerticalFacing::HORIZONTAL)
        ? units::tileToGame(1)
        : kProjectileWidth;
    const auto height = (vertical_direction_ != VerticalFacing::HORIZONTAL)
        ? units::tileToGame(1)
        : kProjectileWidth;

    const auto pos = getPos();
    return Rectangle(pos.x + units::kHalfTile - width / 2,
            pos.y + units::kHalfTile - height / 2,
            width, height);
}

units::HP PolarStar::Projectile::getContactDamage() const
{
    return 1;
}

Vector<units::Game> PolarStar::Projectile::getPos() const
{
    units::Game x = pos_.x;
    units::Game y = pos_.y;
    if (vertical_direction_ == VerticalFacing::HORIZONTAL) {
        x += (horizontal_direction_ == HorizontalFacing::LEFT)
            ? -offset_
            : offset_;
    }
    switch (vertical_direction_) {
    case VerticalFacing::HORIZONTAL:
        break;
    case VerticalFacing::UP:
        y -= offset_;
        break;
    case VerticalFacing::DOWN:
        y += offset_;
        break;
    default: break;
    }
    return Vector<units::Game>{ x, y };
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
                units::tileToPixel(kProjectileSourceWidth),
                units::tileToPixel(kProjectileSourceHeight)
                ));
    vertical_projectile_.reset(new Sprite(
                graphics, "Bullet",
                units::tileToPixel(kVerticalProjectileSourceX),
                units::tileToPixel(kProjectileSourceY),
                units::tileToPixel(kProjectileSourceWidth),
                units::tileToPixel(kProjectileSourceHeight)
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

