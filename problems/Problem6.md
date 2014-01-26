Episode 6: Player Movement
==========================

Problem:

  - Quote needs to walk left/right
    - Which way is Quote facing?
    - Where on the screen is Quote being drawn?

Details:

  - Cave Story uses &larr; and &rarr; for movement
  - When &larr; is pushed
    1. Quote faces left
    2. Quote accelerates left
  - When &larr; is held
    1. Quote accelerates left
    2. Quote does not exceed a maximum (horizontal) speed
  - When &larr; is released
    1. Quote decelerates left, until velocity is 0
  - Similarly for &rarr;
  - When &larr; and &rarr; are pushed at the same time, Quote does not move

Solution:

  - Introduce a Player class which contains
    - sprite
    - x, y, velocity\_x
    - startMovingLeft, startMovingRight, stopMoving
    - no movements will take place in the input-handling methods
    - update, draw
    
  - Equations for walking:
    - x += velocity\_x \* time
    - velocity\_x += acceleration\_x \* time
    - acceleration\_x varies based on Quote's state.
      - Walking Left: acceleration\_x = -walking\_acceleration
      - Walking Right: acceleration\_x = walking\_acceleration
    - velocity\_x also varies based on Quote's state.
      - Walking: (already given)
      - Standing: (not from physics)
        velocity\_x = velocity\_x / slowdown\_constant (around 1.2)
