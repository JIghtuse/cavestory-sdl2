Episode 6: Player Movement
==========================

Problem:

  - Quote needs to walk left/right
    - Which way is Quote facing?
    - Where on the screen is Quote being drawn?

Details:

  - Cave Story uses ← and → for movement
  - When ← is pushed
    1. Quote faces left
    2. Quote accelerates left
  - When ← is held
    1. Quote accelerates left
    2. Quote does not exceed a maximum (horizontal) speed
  - When ← is released
    1. Quote decelerates left, until velocity is 0
  - Similarly for →
  - When ← and → are pushed at the same time, Quote does not move

Solution:

  - Introduce a Player class which contains
    - sprite
    - x, y, velocity_x
    - startMovingLeft, startMovingRight, stopMoving
    - no movements will take place in the input-handling methods
    - update, draw
    
  - Equations for walking:
    - x += velocity_x * time    
    - velocity_x += acceleration_x * time
    - acceleration_x varies based on Quote's state.
      - Walking Left: acceleration_x = -walking_acceleration
      - Walking Right: acceleration_x = walking_acceleration
    - velocity_x also varies based on Quote's state.
      - Walking: (already given)
      - Standing: (not from physics)
        velocity_x = velocity_x / slowdown_constant (around 1.2)