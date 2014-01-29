Episode 13: Collision Detection.
================================

Problem
--------

Tile collisions

Solution (Map)
--------------

Map class:

  - Map.tiles\_
  - Tile class: Sprite and TileType (AIR\_TILE or WALL\_TILE)
  - How do we know if our rectangle is colliding?
    - Map.getCollidingTiles() returns vector&lt;CollisionTile&gt;
    - CollisionTile: row, col, TileType
  - Find all colliding tiles
    - first row = top() / tileSize (truncating)
    - last row = bottom() / tileSize (truncating)
    - first col = left() / tileSize (truncating)
    - last col = right() / tileSize (truncating)

Solution (Player)
-----------------

Player class:

  - Create our X-Collision and Y-Collision rectangles
  - Functions to create left/right/top/bottom rectangles (based on deltas)
  - For each axis:
    - Update velocity
    - Calculate delta
    - Check collision in direction of delta, react to it
    - Check collision in other direction, update position
