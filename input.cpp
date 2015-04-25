#include "input.h"
#include <SDL2/SDL.h>

#include <iostream>

bool* getInput(bool* keysHeld)
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            std::cout << "keydown: " << event.key.keysym.sym << std::endl;
            keysHeld[event.key.keysym.sym] = true;
        }

        if (event.type == SDL_KEYUP)
        {
            std::cout << "keyup: " << event.key.keysym.sym << std::endl;
            keysHeld[event.key.keysym.sym] = false;
        }
    }
    return keysHeld;
};
