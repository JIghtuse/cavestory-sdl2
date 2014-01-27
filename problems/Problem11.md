Episode 11: Creating a Test Map
===============================

Problem:

  - We want to have a map of walls to run into/jump on/jump off of.

Solution:

  - Create the test map before the event loop
  - Map class to hold:
    - Foreground Sprites - as a list
    - CollisionMap - as a CollisionMap Object
  - CollisionMap to hold:
    - CollisionRectangles
