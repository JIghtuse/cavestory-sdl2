Episode 3: Keyboard Input
=========================

Problem:
  - How do we deal with all of the keyboard events?

Details:
  - is a particular key being held?
    - used for: determining key collisions (← and → in particular)
  - has a key just been pressed?
    - used for: jumping, walking (and more)
  - has a key just been released?
    - used for: jumping, walking (and more)

  - evaluate the keypresses in the order we want, not in the order
    SDL gives it to us

Solution:
  - Create an Input class that tracks key presses
  - We will use a std::map<SDL_Scancode, bool>
    Scancode is more universal then key. See
    [MigratoinGuide](http://wiki.libsdl.org/MigrationGuide#Input) for details
  - methods:
    - beginNewFrame() \/\/ To let us know that a new frame has begun

    - keyDownEvent(SDL_Event)
    - keyUpEvent(SDL_Event)

    - bool wasKeyPressed()
    - bool wasKeyReleased()
    - bool isKeyDown()
