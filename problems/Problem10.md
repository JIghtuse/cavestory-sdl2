Episode 10: Vertical Facing and Additional Sprites
==================================================

Problem:

  - Jump animation
  - Keep track of which way Quote is facing Up, Down, or Horizontal?

Solution (Jump):

  - Jump animation (uses frames from walk animation):
    - 2nd frame when going up
    - 3rd frame when falling

Solution (Vertical Facing):

  - More state - Vertical Facing: Up, Down, Horizontal
  - Add VerticalFacing to SpriteState
  - Add new sprites to initializeSprites
