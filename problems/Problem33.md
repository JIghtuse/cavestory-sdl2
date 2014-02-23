Episode 33: Image Paths
=======================

Problem
--------

- Using content paths on sprite creating is annoying
- Need to have easy way to switch between hi-res graphics and original-res
  graphics (in code only)

Solution
--------

- Instead of calling graphics.loadImage with "content/NpcCemet.bmp", just
  call it with "NpcCemet"
- Config file with just GraphicsQuality for now
