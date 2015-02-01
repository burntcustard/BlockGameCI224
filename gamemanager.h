#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "shader.h"
#include "cube.h"
#include "camera.h"
#include "transform.h"
#include "window.h"

class GameManager
{
    public:
        GameManager();
        virtual ~GameManager();
        void loop();
        void update();
    protected:
    private:
    Transform tCube, tCube2;
    Shader shader;
    Camera camera;
    Cube cube, cube2;
};

#endif // GAMEMANAGER_H
