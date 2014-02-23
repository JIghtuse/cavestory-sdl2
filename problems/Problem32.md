Episode 32: Actual Vertical Facing
==================================

Problem
--------

- When the player is on the ground he cannot face down if he intends to

Solution
--------

- Change vertical\_facing\_ to intended\_vertical\_facing\_
- Introduce vertical\_facing() and use this to:
    1 - pass to gun's draw
    2 - clean up spritestates
