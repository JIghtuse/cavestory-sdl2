Episode 40: Damage Texts
========================

Problem
--------

- Damage Text needs to outlive their owners
- Damage Text need to be drawn pretty close to last (but still before the HUD)

Solution
--------

- DamageTexts class to own/update/draw all damage texts
- Interface Damageable: anything that can have a damage text (Player/enemy)
