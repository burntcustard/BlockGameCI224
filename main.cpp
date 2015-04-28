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
std::vector<std::shared_ptr<Cube>> gameworld;
std::vector<std::shared_ptr<Cube>> projectiles;
void updateWorld();
void drawGame(Shader &shader, vector<std::shared_ptr<Cube>> &gameworld, Window &window);

std::map<int, bool> keys;  // List of keycodes with true/false for pressed/not pressed.
std::map<char, int> mouse; // X and Y movement of mouse cursor.
bool isColliding(glm::vec3 aPos, glm::vec3 aScale, glm::vec3 bPos, glm::vec3 bScale);
void fire();
void pGravity();

float playerMoveSpeed = 0.1;                     // Player/cameras movement speed.
float lookSensitivity = 0.2;                     // Sensitivity of camera movement controlled by mouse.
glm::vec3 playerSize = glm::vec3(0.1, 1.0, 0.1); // Player/camera x/y/z dimensions.

void handleInput()
{
    int playerXMovement = 0; // Player/camera side strafing.
    int playerZMovement = 0; // Player/camera forward/back movement.
    int playerYMovement = 0; // Player/camera up/down movement. (Jumping test)

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
                case SDLK_ESCAPE: gameRunning = false;                                          break;
                case SDLK_w     : playerZMovement =  1;                                         break; // Forward
                case SDLK_a     : playerXMovement =  1;                                         break; // Left
                case SDLK_s     : playerZMovement = -1;                                         break; // Back
                case SDLK_d     : playerXMovement = -1;                                         break; // Right
                case SDLK_SPACE : {
                    glm::vec3 legs = glm::vec3(0,-1,0); // Legs that stick out the bottom of camera...
                    for(int i = 0; i < gameworld.size(); i++) {
                        if(isColliding(camera.GetPos()+legs, playerSize, gameworld[i]->t.GetPos(),gameworld[i]->t.GetScale())) {
                            camera.Jump();
                        }
                    }
                } break; // Up
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
        for(int i = 0; i < gameworld.size(); i++)   {
            if(isColliding(gameworld[i]->t.GetPos(),gameworld[i]->t.GetScale(),camera.GetPos(),glm::vec3(0.1,0.1,0.1))){
                camera.Move('z', (-playerZMovement * playerMoveSpeed) / sqrt(2));
                camera.Move('x', (-playerXMovement * playerMoveSpeed) / sqrt(2));
            }
        }
    }
    else
    // Simple one direction movement
    {
        camera.Move('z', (playerZMovement * playerMoveSpeed));
        camera.Move('x', (playerXMovement * playerMoveSpeed));
        for(int i = 0; i < gameworld.size(); i++)   {
            if(isColliding(gameworld[i]->t.GetPos(),gameworld[i]->t.GetScale(),camera.GetPos(),glm::vec3(0.1,0.1,0.1))){
                camera.Move('z', (-playerZMovement * playerMoveSpeed));
                camera.Move('x', (-playerXMovement * playerMoveSpeed));
            }
        }
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

}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(0); // Hide mouse cursor
    SDL_SetRelativeMouseMode(SDL_TRUE); // Capture mouse (prevents stuck when hitting window edge)
    Window window(960,720, "game");

    // GameManager game();

    Shader shader("./res/basicShader");

    cout << "Game started!" << endl;

    gameworld.push_back(std::make_shared<Cube>(4,0,4));
    gameworld.push_back(std::make_shared<Cube>(0,1,3));
    gameworld.push_back(std::make_shared<Cube>(-1,-1,-2));
    gameworld.push_back(std::make_shared<Cube>( 0,-1,-2));
    gameworld.push_back(std::make_shared<Cube>( 1,-1,-2));
    gameworld.push_back(std::make_shared<Cube>(-1,-1,-1));
    gameworld.push_back(std::make_shared<Cube>( 0,-1,-1));
    gameworld.push_back(std::make_shared<Cube>( 1,-1,-1));
    gameworld.push_back(std::make_shared<Cube>(-1,-1, 0));
    gameworld.push_back(std::make_shared<Cube>( 0,-1, 0));
    gameworld.push_back(std::make_shared<Cube>( 1,-1, 0));
    gameworld.push_back(std::make_shared<Cube>(-1,-1, 1));
    gameworld.push_back(std::make_shared<Cube>( 0,-1, 1));
    gameworld.push_back(std::make_shared<Cube>( 1,-1, 1));
    gameworld.push_back(std::make_shared<Cube>( 2, 0, 0));
    gameworld.push_back(std::make_shared<Cube>( 2, 0, 1));
    gameworld.push_back(std::make_shared<Cube>( 2, 0, 2));


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
        if(projectiles.size()>0){
            projectiles[i]->t.GetPos()+= projectiles[i]->t.GetForwards();
        }
    }

    pGravity();

    // Detect collisions:
    for (auto p : projectiles)
    {
        for (auto c : gameworld)
        {
            if (isColliding(p->t.GetPos(), p->t.GetScale(), c->t.GetPos(), c->t.GetScale()))
            {
                // There was a collision and now the two things explode.
                cout << "COLLISION!" << endl;
                p->SetDead();
                c->SetDead();
            }
        }
    }

    // Remove dead projectiles
    std::vector<std::shared_ptr<Cube>> tmpProjectiles;
    for (auto p : projectiles)
    {
        if (!p->IsDead()) tmpProjectiles.push_back(p);
    }
    projectiles.clear();
    projectiles = tmpProjectiles;

    // Remove dead cubes
    std::vector<std::shared_ptr<Cube>> tmpCubes;
    for (auto c : gameworld)
    {
        if (!c->IsDead()) tmpCubes.push_back(c);
    }
    gameworld.clear();
    gameworld = tmpCubes;
}



void fire() {
    projectiles.push_back(std::make_shared<Cube>(camera.GetPos().x, camera.GetPos().y, camera.GetPos().z));
    projectiles[projectiles.size()-1]->t.GetForwards() = camera.GetForward();
    projectiles[projectiles.size()-1]->t.GetScale() = glm::vec3(0.3, 0.3, 0.3);

}

bool isColliding(glm::vec3 aPos, glm::vec3 aScale, glm::vec3 bPos, glm::vec3 bScale) {
    if (!(fabsf(aPos.x - bPos.x) < aScale.x/2 + bScale.x/2)) return false; // Not colliding on x axis
    if (!(fabsf(aPos.y - bPos.y) < aScale.y/2 + bScale.y/2)) return false; // Not colliding on y axis
    if (!(fabsf(aPos.z - bPos.z) < aScale.z/2 + bScale.z/2)) return false; // Not colliding on z axis
    return true; // Colliding on all axis, so actually inside each other!
}

void pGravity() {
    camera.yVelocity -= 0.005;
    if(camera.yVelocity<= -0.1) camera.yVelocity = -0.1;
    camera.Move('y', camera.yVelocity);
    for(int i = 0; i < gameworld.size(); i++)   {
        if(isColliding(gameworld[i]->t.GetPos(), gameworld[i]->t.GetScale(), camera.GetPos(), playerSize)){
            camera.Move('y', -camera.yVelocity);
            camera.yVelocity=0;
        }
    }
}
