#ifndef HEAD_BUMP_PARTICLE_H_
#define HEAD_BUMP_PARTICLE_H_

#include <chrono>
#include "polar_vector.h"
#include "sprite.h"
#include "timer.h"
#include "units.h"
#include "vector.h"

struct Graphics;

struct HeadBumpParticle {
   HeadBumpParticle(Graphics& graphics, Vector<units::Game> center_pos);

   void draw(Graphics& graphics) const;
   bool update(const std::chrono::milliseconds elapsed_time);
private:
   Sprite sprite_;
   Timer live_timer_;
   const Vector<units::Game> center_pos_;
   PolarVector particle_a_;
};

#endif /* HEAD_BUMP_PARTICLE_H_ */
