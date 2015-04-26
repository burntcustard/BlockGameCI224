#include <iostream>
#include <SDL2/SDL.h>
//#include <GL/glew.h>
#include "window.h"
#include "shader.h"
#include "cube.h"
#include "camera.h"
#include "transform.h"
#include "gamemanager.h"
#include <map>
#include "input.h"

using namespace std;

bool gameRunning = true;
std::map<int, bool> keys; // List of keys being pressed.

Camera camera;
Transform tCube;
Transform tCube2;
void drawGame(Shader &shader, Cube &cube, Window &window);

void handleInput()
{
    // Update list of pressed keys with getInput:
    keys = getInput(keys);

    // Loop through all keys that are pressed
    for (auto key : keys)
    {
        if (key.second) // If second value in map (the bool) = true (i.e. if keypressed)
        {
            // Show the name of the key in console:
            cout << "Key down: " << SDL_GetKeyName(key.first) << endl;
            // Check if that key does something important:
            switch (key.first)
            {
                case SDLK_ESCAPE: gameRunning = false;     break;
                case SDLK_a     : camera.MoveRight(0.1);   break;
                case SDLK_d     : camera.MoveRight(-0.1);  break;
                default: break; // No useful keys detected in list of pressed keys
            }
        }
    }

    /*

    SDL_Event event;
    while (SDL_PollEvent(&event))
      {
         if (event.type == SDL_KEYDOWN)
         {
            cout << "keydown: " << event.key.keysym.sym << endl;
            switch (event.key.keysym.sym)
            {
               case SDLK_ESCAPE:
                  gameRunning = false;
               break;
               case SDLK_w:
                  camera.MoveForward(0.1);
                  //if(abs(camera.GetPos().x-cube.t.GetPos().x)<=1 && abs(camera.GetPos().y-cube.t.GetPos().y)<=1 && abs(camera.GetPos().z-cube.t.GetPos().z)<=1)
                  //{
                    //camera.MoveForward(-0.1);
                  //}
                  if(abs(camera.GetPos().x-tCube2.GetPos().x)<=1 && abs(camera.GetPos().y-tCube2.GetPos().y)<=1 && abs(camera.GetPos().z-tCube2.GetPos().z)<=1)
                  {
                    camera.MoveForward(-0.1);
                  }
                break;

                case SDLK_s:
                  camera.MoveForward(-0.1);
                  if(abs(camera.GetPos().x-tCube.GetPos().x)<=1 && abs(camera.GetPos().y-tCube.GetPos().y)<=1 && abs(camera.GetPos().z-tCube.GetPos().z)<=1)
                  {
                    camera.MoveForward(0.1);
                  }
                  if(abs(camera.GetPos().x-tCube2.GetPos().x)<=1 && abs(camera.GetPos().y-tCube2.GetPos().y)<=1 && abs(camera.GetPos().z-tCube2.GetPos().z)<=1)
                  {
                    camera.MoveForward(0.1);
                  }
                break;

                case SDLK_d:
                  camera.MoveRight(-0.1);
                  if(abs(camera.GetPos().x-tCube.GetPos().x)<=1 && abs(camera.GetPos().y-tCube.GetPos().y)<=1 && abs(camera.GetPos().z-tCube.GetPos().z)<=1)
                  {
                    camera.MoveRight(0.1);
                  }
                  if(abs(camera.GetPos().x-tCube2.GetPos().x)<=1 && abs(camera.GetPos().y-tCube2.GetPos().y)<=1 && abs(camera.GetPos().z-tCube2.GetPos().z)<=1)
                  {
                    camera.MoveRight(0.1);
                  }
                break;
                case SDLK_a:
                  camera.MoveRight(0.1);
                  if(abs(camera.GetPos().x-tCube.GetPos().x)<=1 && abs(camera.GetPos().y-tCube.GetPos().y)<=1 && abs(camera.GetPos().z-tCube.GetPos().z)<=1)
                  {
                    camera.MoveRight(-0.1);
                  }
                  if(abs(camera.GetPos().x-tCube2.GetPos().x)<=1 && abs(camera.GetPos().y-tCube2.GetPos().y)<=1 && abs(camera.GetPos().z-tCube2.GetPos().z)<=1)
                  {
                    camera.MoveRight(-0.1);                  }
                break;
            }
         }
         if (event.type == SDL_MOUSEMOTION)
         {
            camera.RotateY(-event.motion.xrel/2);
            camera.Pitch(event.motion.yrel/2);
         }
      }
      */

}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(0);
    Window window(960,720, "game");

   // GameManager game();

    Shader shader("./res/basicShader");

  //  Camera camera;
    Cube cube;
 //   Transform tCube;
    Cube cube2;
//    Transform tCube2;
    cout << "Hello world!" << endl;
    tCube.GetPos().z=4;
    tCube2.GetPos().z=3;
    tCube2.GetPos().x=2;
    //tCube.GetRot().y=45;
    tCube.GetRot().z=90;
    cube.t.GetPos().x=4;
    cube.t.GetPos().z=4;

    while(!window.IsClosed() && gameRunning)
    {

        handleInput();

        // cout << cube.t.GetPos().x << endl;
        tCube.GetRot().x+=2;
   //     tCube.GetPos().y+=0.01;
        tCube2.GetRot().z+=2;
      //  camera.Pitch(1);
        drawGame(shader, cube, window);

    }
    SDL_QUIT;
    return 0;
}

void drawGame(Shader &shader, Cube &cube, Window &window){
    glClearColor(0.0f, 0.15f, 0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader.Update(cube.t,camera);
    cube.Draw();
    shader.Update(tCube2,camera);
    cube.Draw();
    shader.Bind();
    window.Update();
}
