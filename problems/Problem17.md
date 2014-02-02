Episode 17: Multiple Resolutions
================================

Problem
--------

- The original Cave Story uses 16x16 sprites and 320x240 screen size.
- Media content can be taken from Nicalis' Cave Story (steam), (humblebundle)

Solution
--------

- .pbm files are really .bmp files with a (C)Pixel appended.
- Convert all pixel values to screen-size agnostic values.
    - motion constants
    - collision rectangles
    - backdrop tiles
