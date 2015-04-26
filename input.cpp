#include "input.h"
#include <SDL2/SDL.h>

#include <map>
#include <iostream>

std::map<int, bool> getInput(std::map<int, bool> keys)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            std::cout << "keydown: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
            keys[event.key.keysym.sym] = true;
        }

        if (event.type == SDL_KEYUP)
        {
            std::cout << "keyup: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
            keys[event.key.keysym.sym] = false;
        }
    }
    return keys;
};
