Episode 36: Projectiles Life Span
=================================

Problem
--------

- Projectiles need to move in the direction they are fired
- Projectiles need to be removed when they reach the end of their lifespan
- Polar Star limited 2 projectiles onscreen at any one time

Solution
--------

- update(elapsed\_time) method for Projectile (use offset and velocity)
- startFire(): allow only 2 projectiles
