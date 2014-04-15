#include "damage_texts.h"
#include "damageable.h"
#include "damage_text.h"

DamageTexts::DamageTexts() :
    damage_text_map_()
{}


void DamageTexts::update(std::chrono::milliseconds elapsed_time)
{
    for (auto pair : damage_text_map_) {
        if (!pair.second.expired()) {
            std::shared_ptr<Damageable> damageable(pair.second);
            pair.first->setCenterPosition(damageable->getCenterPos());
        }
        // Owner still alive or timer is not expired - damage text still exists
        if (pair.first->update(elapsed_time) || !pair.second.expired()) {
            continue;
        } else {
            damage_text_map_.erase(pair.first);
        }
    }
}

void DamageTexts::draw(Graphics& graphics) const
{
    for (auto pair : damage_text_map_) {
        pair.first->draw(graphics);
    }
}

void DamageTexts::addDamageable(std::shared_ptr<Damageable> damageable)
{
    auto damage_text_ = damageable->getDamageText();
    damage_text_map_[damage_text_] = std::weak_ptr<Damageable>(damageable);

}
