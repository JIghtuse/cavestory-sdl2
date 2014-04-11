#ifndef POLAR_STAR_H_
#define POLAR_STAR_H_

#include <chrono>
#include <vector>
#include "projectile.h"
#include "rectangle.h"
#include "sprite_state.h"
#include "units.h"
#include "vector.h"

struct Graphics;
struct Map;
struct Sprite;

struct PolarStar {
    PolarStar(Graphics& graphics);
    ~PolarStar();

    void updateProjectiles(std::chrono::milliseconds elapsed_time,
            const Map& map);
    void draw(Graphics& graphics,
            const HorizontalFacing horizontal_facing,
            const VerticalFacing vertical_facing,
            bool gun_up,
            Vector<units::Game> player_pos) const;
    void startFire(const Vector<units::Game> player_pos,
            const HorizontalFacing hfacing,
            const VerticalFacing vfacing,
            bool gun_up
            );
    void stopFire();
    std::vector<std::shared_ptr<GenericProjectile> > getProjectiles();
private:
    const Vector<units::Game> calcGunPos(
            const Vector<units::Game> player_pos,
            const HorizontalFacing hfacing,
            const VerticalFacing vfacing,
            const bool gun_up
            ) const;
    const Vector<units::Game> getBulletPos(
            const Vector<units::Game> player_pos,
            const HorizontalFacing hfacing,
            const VerticalFacing vfacing
            ) const;

    struct Projectile : public GenericProjectile {
        Projectile(std::shared_ptr<Sprite> sprite,
                const HorizontalFacing hdirection,
                const VerticalFacing vdirection,
                const Vector<units::Game> pos);
        // Returns true if |this} are alive.
        bool update(std::chrono::milliseconds elapsed_time, const Map& map);
        void draw(Graphics& graphics) const;
        Rectangle getCollisionRectangle() const;
        units::HP getContactDamage() const;
        void collideWithEnemy();
    private:
        Vector<units::Game> getPos() const;

        Vector<units::Game> pos_;
        HorizontalFacing horizontal_direction_;
        VerticalFacing vertical_direction_;
        std::shared_ptr<Sprite> sprite_;
        units::Game offset_;
        bool alive_;
    };

    struct SpriteState {
        SpriteState(
                HorizontalFacing horizontal_facing,
                VerticalFacing vertical_facing
                ) :
            horizontal_facing{horizontal_facing},
            vertical_facing{vertical_facing}
        {}

        HorizontalFacing horizontal_facing;
        VerticalFacing vertical_facing;
    };
    friend bool operator<(const SpriteState& a, const SpriteState& b);

    void initializeSprites(Graphics& graphics);
    void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);

    std::map<SpriteState, std::shared_ptr<Sprite> > sprite_map_;
    std::shared_ptr<Sprite> horizontal_projectile_;
    std::shared_ptr<Sprite> vertical_projectile_;
    std::shared_ptr<Projectile> projectile_a_;
    std::shared_ptr<Projectile> projectile_b_;
};

#endif /* POLAR_STAR_H_ */

