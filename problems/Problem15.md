Episode 15: Introducing the Background
======================================

Problem
--------

- Need to add background
- Quote is actually drawing black pixels to the screen

Solution
--------

- Layers
    - Foreground Layer: wall tile, water tiles
    - Entity Layer(s): Quote, enemies, doors
    - Background Layer: background tiles, chain tiles
    - Backdrop: stuff in the different background. Sometimes solid color,
      sometimes cave texture
          - Fixed position
          - Parallax / other
- Draw a backdrop
- Draw background tiles
