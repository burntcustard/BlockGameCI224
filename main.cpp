#include <iostream>
#include <SDL2/SDL.h>
//#include <GL/glew.h>
#include "window.h"
#include "shader.h"
#include "cube.h"
#include "camera.h"
#include "transform.h"
#include "gamemanager.h"

using namespace std;

Camera camera;
Transform tCube;
Transform tCube2;

void handleInput()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
      {


         if (event.type == SDL_KEYDOWN)
         {
         //   cout << "keydown" << endl;
            switch (event.key.keysym.sym)
            {
               case SDLK_w:
                  camera.MoveForward(0.1);
                  if(abs(camera.GetPos().x-tCube.GetPos().x)<=1 && abs(camera.GetPos().y-tCube.GetPos().y)<=1 && abs(camera.GetPos().z-tCube.GetPos().z)<=1)
                  {
                    camera.MoveForward(-0.1);
                  }
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
}

int main()
{

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(0);
    Window window(1280,720, "game");

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

    while(!window.IsClosed())
    {
        glClearColor(0.0f, 0.15f, 0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        handleInput();

        tCube.GetRot().x+=2;
   //     tCube.GetPos().y+=0.01;
        tCube2.GetRot().z+=2;
      //  camera.Pitch(1);

        shader.Update(tCube,camera);
        cube.Draw();
        shader.Update(tCube2,camera);
        cube2.Draw();
        shader.Bind();
        window.Update();
    }
    SDL_QUIT;
    return 0;
}
