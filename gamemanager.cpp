#include "gamemanager.h"

GameManager::GameManager()
{
    Shader shader("./res/basicShader");
    Camera camera;
    Cube cube;
    Transform tCube;
    Cube cube2;
    Transform tCube2;
//    cout << "Hello world!" << endl;
    tCube.GetPos().z=4;
    tCube2.GetPos().z=3;
    tCube2.GetPos().x=2;
}

GameManager::~GameManager()
{
    //dtor
}

void GameManager::update()
{
        tCube.GetRot().y+=5;
        tCube2.GetRot().x+=4;
        shader.Update(tCube,camera);
        cube.Draw();
        shader.Update(tCube2,camera);
        cube2.Draw();
        shader.Bind();
}
