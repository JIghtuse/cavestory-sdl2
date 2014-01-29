Episode 12: Collision Detection. Tile Based. Axis-Aligned Bounding Box.
=======================================================================

Problem:

  - We need to implement collision detection

Solution:

  - Collisions will be detected using Collision Rectangles for Quote
    - Y collision rectangle will be different from X collision rectangle
  - Collision Rectangles have: x, y, width, height
  - Tile:
    - 32x32 Rectangles
    - Absolute (row, col) position
  - The algorithm
    - Four collision detections: left, right, top, bottom
    - We will split Quote's collision rectangles in half
    - Include amount moved (delta) in rectangles

Solution (X axis):

  - Calculate delta\_x (amount moved in x)
  - If delta\_x &gt;= 0, do right side first, otherwise left
  - Create a rectangle including delta\_x
  - Check to see if our collision rectangle intersects a tile
  - If it does: move it just enough to not be intersecting
  - Repeat for the other side with new position

Solution (Y axis):

  - Calculate delta\_y (amount moved in y)
  - If delta\_y &gt;= 0, do bottom side first, otherwise top
  - Create a rectangle including delta\_y
  - Check to see if our collision rectangle intersects a tile
  - If it does: move it just enough to not be intersecting
  - Repeat for the other side with new position
