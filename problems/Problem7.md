Episode 6: Spritesheet Cache
============================

Problem:

  - Many sprites use one spritesheet (stand, walk left, walk right, etc.)
  - Loading the same spritesheet over and over again.

Solution:

  - Create a cache of the spritesheets in CPU memory.
  - Sprites will no longer have 'control' of SDL\_Textures
  - Store SDL\_Textures in the Graphics class
  - std::map&lt;std::string file\_path, SDL\_Texture\*&gt; sprite\_sheets
