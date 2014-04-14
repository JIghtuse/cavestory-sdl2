#ifndef DAMAGEABLE_H_
#define DAMAGEABLE_H_

#include <memory>
#include "units.h"
#include "vector.h"

struct DamageText;

struct Damageable {
   Damageable();
   virtual ~Damageable() {};
   virtual Vector<units::Game> getCenterPos() const = 0;
   virtual std::shared_ptr<DamageText> getDamageText() const = 0;
};

#endif /* DAMAGEABLE_H_ */
