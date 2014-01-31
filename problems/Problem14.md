Episode 14: Refining Player Movement
====================================

Problem
--------

- Jump is actually a reduced gravity, not anti-gravity
- Motion constants are a bit off (jumping too high)
- Player's "look back" needs refinement
    - don't look back if coming down from a jump
    - stay looking back until jump/look-up/walk is pressed

Solution
--------

- We'll make our jump reduced gravity, and remove the timer
- [Cave Story Physics](https://docs.google.com/document/d/1wr7RKzmb0UC2abh_2HfyIMN8N-JDGwBFaNHUJmpKxRs/edit?hl=en) (Google Doc)
- Introduce "INTERACTING" motion\_type
