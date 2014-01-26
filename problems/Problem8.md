Episode 8: Multiple Sprites
===========================

Problem:

  - Quote needs to be able to switch between sprites, based on his state.

Solution:

  - Introduce a map from state -&gt; sprites.
  - SpriteState will need to know:
    1. Are we walking?
    2. Are we facing left/right?
  - For std::map we need an operator&lt; definition to our keys
