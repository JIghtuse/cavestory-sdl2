#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "rectangle.h"
#include "units.h"

struct GenericProjectile {
   virtual Rectangle getCollisionRectangle() const = 0;
   virtual units::HP getContactDamage() const = 0;
   virtual void collideWithEnemy() = 0;
   virtual ~GenericProjectile() {};
};

#endif /* PROJECTILE_H_ */

