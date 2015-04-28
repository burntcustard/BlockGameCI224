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
#include <vector>
#include <utility>
#include <memory>

using namespace std;

bool gameRunning = true;

Input input;
Camera camera;
Transform tCube;
Transform tCube2;
std::vector<std::shared_ptr<Cube>> projectiles;
void updateWorld();

void drawGame(Shader &shader, vector<std::shared_ptr<Cube>> &gameworld, Window &window);

std::map<int, bool> keys;  // List of keycodes with true/false for pressed/not pressed.
std::map<char, int> mouse; // X and Y movement of mouse cursor.

void fire() {
    projectiles.push_back(std::make_shared<Cube>(camera.GetPos().x, camera.GetPos().y, camera.GetPos().z));
    projectiles[projectiles.size()-1]->t.GetForwards()=camera.GetForward();
}

void handleInput()
{
    float playerMoveSpeed = 0.1; // Player/cameras movement speed.
    float lookSensitivity = 0.2; // Sensitivity of camera movement controlled by mouse.
    int playerXMovement = 0;     // Player/camera side strafing.
    int playerZMovement = 0;     // Player/camera forward/back movement.
    int playerYMovement = 0;     // Player/camera up/down movement. (Jumping test)

    // Update inputs and handle events
    input.updateInput();

    // Update list of pressed keys with getKeys:
    keys = input.getKeys();

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
                case SDLK_ESCAPE: gameRunning = false;  break;
                case SDLK_w     : playerZMovement =  1; break; // Forward
                case SDLK_a     : playerXMovement =  1; break; // Left
                case SDLK_s     : playerZMovement = -1; break; // Back
                case SDLK_d     : playerXMovement = -1; break; // Right
                case SDLK_SPACE : playerYMovement =  1; break; // Up
                case SDLK_LSHIFT: playerYMovement = -1; break; // Down
                default: break; // No useful keys detected in list of pressed keys
            }
        }
    }

    // Sideways (x-axis & z-axis) (along the ground) movement.
    if (playerXMovement && playerZMovement)
    // Diagonal movement - stops you moving too fast when going forward AND sideways
    {
        camera.Move('z', (playerZMovement * playerMoveSpeed) / sqrt(2));
        camera.Move('x', (playerXMovement * playerMoveSpeed) / sqrt(2));
    }
    else
    // Simple one direction movement
    {
        camera.Move('z', (playerZMovement * playerMoveSpeed));
        camera.Move('x', (playerXMovement * playerMoveSpeed));
    }

    // Up / down (y-axis) (jumping etc.) movement.
    camera.Move('y', (playerYMovement * playerMoveSpeed));

    // Get mouse cursor movement changes:
    mouse = input.getMouse();
    // If mouse has moved, spit it into console:
    if (mouse['x'] | mouse['y']) cout << "Mouse moved X: " << mouse['x'] << ", Y: " << mouse['y'] << endl;

    // Rotate camera
    camera.RotateX(mouse['x'] * lookSensitivity); // Look left/right
    camera.RotateY(mouse['y'] * lookSensitivity); // Look up/down

    // Mouse buttons (should be done with keyboard shortcuts?)
    if (mouse['l']) fire();

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
    SDL_ShowCursor(0); // Hide mouse cursor
    SDL_SetRelativeMouseMode(SDL_TRUE); // Capture mouse (prevents stuck when hitting window edge)
    Window window(960,720, "game");

   // GameManager game();

    Shader shader("./res/basicShader");

  //  Camera camera;
    //Cube cube;
 //   Transform tCube;
    //Cube cube2;
//    Transform tCube2;
    cout << "Hello world!" << endl;
    //tCube.GetPos().z=4;
    //tCube2.GetPos().z=3;
    //tCube2.GetPos().x=2;
    //tCube.GetRot().y=45;
    //tCube.GetRot().z=90;
    //cube.t.GetPos().x=4;
    //cube.t.GetPos().z=4;
    std::vector<std::shared_ptr<Cube>> gameworld; //vector<std::shared_ptr<Cube>>
    gameworld.push_back(std::make_shared<Cube>(4,0,4));
    gameworld.push_back(std::make_shared<Cube>(0,1,3));


    while(!window.IsClosed() && gameRunning)
    {

        handleInput();

        updateWorld();

        drawGame(shader, gameworld, window);

    }
    SDL_QUIT;
    return 0;
}


//draw everything
void drawGame(Shader &shader, vector<std::shared_ptr<Cube>> &gameworld, Window &window){
    glClearColor(0.0f, 0.15f, 0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // This makes sense so removed old commented out version (but comments on each line might be useful too!
    for(int i = 0; i < gameworld.size(); i++)
    {
        shader.Update(gameworld[i]->t,camera);
        gameworld[i]->Draw();
    }

    for(int i = 0; i < projectiles.size(); i++)
    {
        shader.Update(projectiles[i]->t,camera);
        projectiles[i]->Draw();
    }

    shader.Bind();
    window.Update();
}

void updateWorld(){

    for(int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i]->t.GetPos()+= projectiles[i]->t.GetForwards();
    }
}
