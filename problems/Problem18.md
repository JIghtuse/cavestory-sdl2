Episode 18: Units
=================

Problem
--------

- Using ints and floats for tilesizes and pixels is ambiguous: we need to
  remember what the variable we have and cast to it every time we access it.

Solution - Units
----------------

- Spacial
    - Game (intrinsic)
        - when 32x32 &rarr; 1 Game == 1 Pixel
        - when 16x16 &rarr; 1 Game == 2 Pixels
    - Pixels
    - Tile
        - 1 Tile == 32 Game

- Time
    - Hz (1 / seconds)
    - Milliseconds

- Combination:
    - Game / ms
    - Game / ms / ms
