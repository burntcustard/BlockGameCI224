#include "input.h"
#include <SDL2/SDL.h>

Input::Input()
{
    // TODO: Make sure all inputs are initially set to false.
}

Input::~Input()
{
    // Anything that needs to be done when never accepting input again.
}

void Input::updateInput()
{
    // !WARNING! Can only use one SDL_PollEvent otherwise they interfere with each other.
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            keys[event.key.keysym.sym] = true;
        }

        if (event.type == SDL_KEYUP)
        {
            keys[event.key.keysym.sym] = false;
        }

        // Mouse button pressed
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            // Left mouse button pressed
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mouse['l'] = true;
            }
            // Right mouse button pressed
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                mouse['r'] = true;
            }
        }

        // Mouse button released
        if (event.type == SDL_MOUSEBUTTONUP)
        {
            // Left mouse button pressed
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mouse['l'] = false;
            }
            // Right mouse button pressed
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                mouse['r'] = false;
            }
        }

        if (event.type == SDL_MOUSEMOTION)
        {
            mouse['x'] = event.motion.xrel;
            mouse['y'] = event.motion.yrel;
        }

        if (event.type == SDL_QUIT) // Triggered on things like alt+f4
        {
            keys[SDLK_ESCAPE] = true; // Makes esc basically pressed, kinda dodgy.
        }
    }
};

std::map<int, bool> Input::getKeys()
{
    return keys;
}

std::map<char, int> Input::getMouse()
{
    std::map<char, int> mouseOutput = mouse; // Temporary var storing what will be returned.

    mouse.erase('x'); // Remove x and y values so that next time getMouse() is called, it doesn't
    mouse.erase('y'); // return them unless they have changed since last SDL_MOUSEMOTION event.

    return mouseOutput;
}
