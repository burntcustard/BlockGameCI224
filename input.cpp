#include "input.h"
#include <SDL2/SDL.h>

std::map<int, bool> getInput(std::map<int, bool> keys)
{
    // !WARNING! Can only use one SDL_PollEvent otherwise they interfere with eachother.
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

        if (event.type == SDL_QUIT) // Triggered on things like alt+f4
        {
            keys[SDLK_ESCAPE] = true; // Makes esc basically pressed, kinda dodgy.
        }
    }
    return keys;
};
