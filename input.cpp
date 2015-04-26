#include "input.h"
#include <SDL2/SDL.h>

input::input()
{
    // TODO: Make sure all the keys are set to false.
}

input::~input()
{
    // Anything that needs to be done when never accepting input again.
}

void input::updateInput()
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

        if (event.type == SDL_MOUSEMOTION)
        {
            mouse = std::make_pair(event.motion.xrel/2, event.motion.yrel/2);
        }

        if (event.type == SDL_QUIT) // Triggered on things like alt+f4
        {
            keys[SDLK_ESCAPE] = true; // Makes esc basically pressed, kinda dodgy.
        }
    }
};

std::map<int, bool> input::getKeys()
{
    return keys;
}

std::pair<int, int> input::getMouse()
{
    return mouse;
}
