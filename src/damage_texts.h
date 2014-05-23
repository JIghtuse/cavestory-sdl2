#ifndef DAMAGE_TEXTS_H_
#define DAMAGE_TEXTS_H_

#include <chrono>
#include <map>
#include <memory>
#include "units.h"

struct Damageable;
struct DamageText;
struct Graphics;

struct DamageTexts {
   DamageTexts();
   void update(const std::chrono::milliseconds elapsed_time);
   void draw(Graphics& graphics) const;
   void addDamageable(const std::shared_ptr<Damageable> damageable);
private:
   typedef std::map<std::shared_ptr<DamageText>, std::weak_ptr<Damageable> >
       DamageTextMap;

   DamageTextMap damage_text_map_;
};

#endif /* DAMAGE_TEXTS_H_ */
