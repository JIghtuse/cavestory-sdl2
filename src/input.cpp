#include "input.h"

Input::Input() :
    held_keys_(),
    pressed_keys_(),
    released_keys_()
{}

void Input::beginNewFrame()
{
    pressed_keys_.clear();
    released_keys_.clear();
}

void Input::keyDownEvent(const SDL_Event& event)
{
    pressed_keys_[event.key.keysym.scancode] = true;
    held_keys_[event.key.keysym.scancode] = true;
}

void Input::keyUpEvent(const SDL_Event& event)
{
    released_keys_[event.key.keysym.scancode] = true;
    held_keys_[event.key.keysym.scancode] = false;
}

bool Input::wasKeyPressed(SDL_Scancode key)
{
    return pressed_keys_[key];
}

bool Input::wasKeyReleased(SDL_Scancode key)
{
    return released_keys_[key];
}

bool Input::isKeyHeld(SDL_Scancode key)
{
    return held_keys_[key];
}
