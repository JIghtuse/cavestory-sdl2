#include "damage_text.h"
#include "damage_texts.h"

DamageTexts::DamageTexts() :
    damage_text_map_()
{}


void DamageTexts::update(std::chrono::milliseconds elapsed_time)
{
    for (auto pair : damage_text_map_) {
        pair.first->update(elapsed_time);
    }
}

void DamageTexts::draw(Graphics& graphics) const
{
    for (auto pair : damage_text_map_) {
        pair.first->draw(graphics);
    }
}
