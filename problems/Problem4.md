Episode 4: Animated Sprite
==========================

Problem:
  - We want to see Quote's walk animation!

Details:
  - each frame takes the same amount of time
  - animation keeps looping forever

Solution:
  - Create an Animated Sprite class
    - Needs to be updated before drawn
    - Needs all of the functionality of our Sprite class
    - In addition, keeps track of:
         number of frames,
         current frame,
         time per frame,
         time since the last frame-change
  - Our assumptions about the Bitmap:
         frames are laid out left to right
         frames are spaced at tile\_size
