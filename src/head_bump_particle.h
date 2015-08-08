#ifndef HEAD_BUMP_PARTICLE_H_
#define HEAD_BUMP_PARTICLE_H_

#include <chrono>
#include "particle.h"
#include "polar_vector.h"
#include "sprite.h"
#include "timer.h"
#include "units.h"
#include "vector.h"

struct Graphics;

struct HeadBumpParticle : public Particle {
   HeadBumpParticle(Graphics& graphics, Vector<units::Game> center_pos);

   void draw(Graphics& graphics) const;
   bool update(const std::chrono::milliseconds elapsed_time);
private:
   Sprite sprite_;
   Timer live_timer_;
   const Vector<units::Game> center_pos_;
   PolarVector particle_a_;
   PolarVector particle_b_;
   const units::Game game_max_offset_a_;
   const units::Game game_max_offset_b_;
};

#endif /* HEAD_BUMP_PARTICLE_H_ */
