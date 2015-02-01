#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SDL2/SDL.h>
#include "window.h"
#include "shader.h"
#include "cube.h"
#include "camera.h"
#include "transform.h"
#include "gamemanager.h"

using namespace std;

class game
{
    public:
        game();
        virtual ~game();
        void loop();
    protected:
    private:
    Shader shader;
    Cube cube;
    Cube cube2;
    Transform tCube;
    Transform tCube2;
    Camera camera;
};

#endif // GAME_H
