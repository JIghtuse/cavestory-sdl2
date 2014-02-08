Episode 19: Limit Frame Time
============================

Problem
--------

- Windows-specific bug (crash on window dragging)

Solution
--------

- Create a frame time cap
- Watch for Windows events and keep track of a pause timer
