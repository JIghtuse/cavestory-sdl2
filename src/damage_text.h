#ifndef DAMAGE_TEXT_H_
#define DAMAGE_TEXT_H_

#include <chrono>
#include "timer.h"
#include "vector.h"
#include "units.h"

struct Graphics;

struct DamageText {
   DamageText();
   ~DamageText();

   void update(std::chrono::milliseconds elapsed_time);
   void draw(Graphics& graphics, Vector<units::Game> pos_center) const;

   void setDamage(units::HP damage);
private:
   units::Game offset_y_;
   units::HP damage_;
   Timer damage_timer_;
   bool should_rise_;
};

#endif /* DAMAGE_TEXT_H_ */
