#ifndef POLAR_STAR_H_
#define POLAR_STAR_H_

#include "sprite_state.h"
#include "units.h"
#include "vector.h"

struct Graphics;
struct Sprite;

struct PolarStar {
    PolarStar(Graphics& graphics);
    ~PolarStar();

    void draw(Graphics& graphics,
            const HorizontalFacing horizontal_facing,
            const VerticalFacing vertical_facing,
            bool gun_up,
            Vector<units::Game> player_pos) const;
    void startFire(
            const Vector<units::Game> player_pos,
            const HorizontalFacing hfacing,
            const VerticalFacing vfacing,
            bool gun_up
            );
    void stopFire();
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

    struct Projectile {
        Projectile(std::shared_ptr<Sprite> sprite,
                const HorizontalFacing hdirection,
                const VerticalFacing vdirection,
                const Vector<units::Game> pos);
        void draw(Graphics& graphics) const;
    private:
        Vector<units::Game> pos_;
        HorizontalFacing horizontal_direction_;
        VerticalFacing vertical_direction_;
        std::shared_ptr<Sprite> sprite_;
        units::Game offset_;
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
    std::shared_ptr<Projectile> projectile_;
};

#endif /* POLAR_STAR_H_ */

