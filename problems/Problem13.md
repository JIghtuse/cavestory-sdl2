Episode 13: Collision Detection. Get Colliding Tiles from the Map
=================================================================

Problem
--------

Tile collisions

Solution
--------

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
