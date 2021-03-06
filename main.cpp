#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include "window.h"
#include "shader.h"
#include "cube.h"
#include "camera.h"
#include "transform.h"
#include "gamemanager.h"
#include "level.h"
#include "input.h"

bool gameRunning = true;

// Configurable player/camera variables:
float playerMoveSpeed = 0.05; // Player movement speed.
int playerAirControl = 15;    // Player movement control while in the air. 1 = Full control, higher = less.
float lookSensitivity = 0.8;  // Sensitivity of camera movement controlled by mouse.
glm::vec3 playerSize = glm::vec3(0.2, 0.6, 0.2); // Player/camera x/y/z dimensions (e.g. hitbox).

// Variables to store the players current properties/inputs etc:
std::map<int, bool> keys;  // List of keycodes with true/false for pressed/not pressed.
std::map<char, int> mouse; // X and Y movement of mouse cursor.
glm::vec3 playerMovement = glm::vec3(0,0,0);
// x : Player/camera side strafing.
// y : Player/camera up/down movement.
// z : Player/camera forward/back movement.

// Variables to store the levels current properties (cubes that are in it etc.):
std::vector<std::shared_ptr<Cube>> gameworld;
std::vector<std::shared_ptr<Cube>> projectiles;

// Initialize stuff:
Input input;
Camera camera(playerSize);
Level level;


bool isColliding(glm::vec3 aPos, glm::vec3 aScale, glm::vec3 bPos, glm::vec3 bScale) {
    if (!(fabsf(aPos.x - bPos.x) < aScale.x/2 + bScale.x/2)) return false; // Not colliding on x axis
    if (!(fabsf(aPos.y - bPos.y) < aScale.y/2 + bScale.y/2)) return false; // Not colliding on y axis
    if (!(fabsf(aPos.z - bPos.z) < aScale.z/2 + bScale.z/2)) return false; // Not colliding on z axis
    return true; // Must be colliding on all axis to get to here, so two objects are actually inside each other!
}


/**
 * Figures out if the player is standing on the ground.
 * Use isGrounded(0) for collision detection (e.g. to stop player falling into the ground from gravity).
 *
 * @param offset An OPTIONAL variable that "goes a little deeper" into the ground, to actually be low
 *               enough to go into the block under the player and collide with it.
 *
 */
bool isGrounded(float offset = 0.1)
{
    glm::vec3 vOffset = glm::vec3(0,offset,0);
    for (auto c : gameworld)
    {
        if(isColliding(camera.GetPos()-vOffset, playerSize, c->t.GetPos(), c->t.GetScale()))
            return true;
    }
    return false;
}


void fire()
{
    projectiles.push_back(std::make_shared<Cube>(camera.GetPos().x, camera.GetPos().y, camera.GetPos().z));
    projectiles[projectiles.size()-1]->t.GetForwards() = camera.GetForward();
    projectiles[projectiles.size()-1]->t.GetScale() = glm::vec3(0.3, 0.3, 0.3);
}


void pGravity()
{
    camera.yVelocity -= 0.006;
    if (camera.yVelocity <= -0.1) camera.yVelocity = -0.1;
    camera.Move('y', camera.yVelocity);
    if(isGrounded(0))
    {
        camera.Move('y', -camera.yVelocity);
        camera.yVelocity = 0;
    }
}


void handleInput()
{
    glm::vec3 newPlayerMovement = glm::vec3(0,0,0);

    // If you're on the ground, set movement to 0 (as soon as you let go of WASD you stop).
    if (isGrounded()) playerMovement = glm::vec3(0,0,0);

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
            std::cout << "Key down: " << SDL_GetKeyName(key.first) << std::endl;
            // Check if that key does something important:
            switch (key.first)
            {
                case SDLK_ESCAPE: gameRunning = false;         break;
                case SDLK_w     : newPlayerMovement.z =  1;        break; // Forward
                case SDLK_a     : newPlayerMovement.x =  1;        break; // Left
                case SDLK_s     : newPlayerMovement.z = -1;        break; // Back
                case SDLK_d     : newPlayerMovement.x = -1;        break; // Right
                case SDLK_SPACE : if (isGrounded()) camera.Jump(); break; // Up
                case SDLK_LSHIFT: playerMovement.y = -1; break; // Down
                default: break; // No useful keys detected in list of pressed keys
            }
        }
    }

    if (isGrounded())
    // Player on the ground, has full movement control.
    {
        playerMovement = newPlayerMovement;
    }
    else
    // Player in the air, has squishy air control.
    {
        if (fabsf(playerMovement.x + newPlayerMovement.x / playerAirControl) <= 1)
            playerMovement.x += newPlayerMovement.x / playerAirControl;
        if (fabsf(playerMovement.z + newPlayerMovement.z / playerAirControl) <= 1)
            playerMovement.z += newPlayerMovement.z / playerAirControl;
    }

    // Sideways (x-axis & z-axis) (along the ground) movement.
    if (playerMovement.x && playerMovement.z)
    // Diagonal movement - stops you moving too fast when going forward AND sideways
    {
        camera.Move('z', (playerMovement.z * playerMoveSpeed) / sqrt(2));
        camera.Move('x', (playerMovement.x * playerMoveSpeed) / sqrt(2));
        for(int i = 0; i < gameworld.size(); i++)   {
            if(isColliding(gameworld[i]->t.GetPos(),gameworld[i]->t.GetScale(),camera.GetPos(),playerSize)){
                camera.Move('z', (-playerMovement.z * playerMoveSpeed) / sqrt(2));
                camera.Move('x', (-playerMovement.x * playerMoveSpeed) / sqrt(2));
                playerMovement.z = 0;
                playerMovement.x = 0;
            }
        }
    }
    else
    // Simple one direction movement
    {
        camera.Move('z', (playerMovement.z * playerMoveSpeed));
        camera.Move('x', (playerMovement.x * playerMoveSpeed));
        for(int i = 0; i < gameworld.size(); i++)   {
            if(isColliding(gameworld[i]->t.GetPos(),gameworld[i]->t.GetScale(),camera.GetPos(),playerSize)){
                camera.Move('z', (-playerMovement.z * playerMoveSpeed));
                camera.Move('x', (-playerMovement.x * playerMoveSpeed));
                playerMovement.z = 0;
                playerMovement.x = 0;
            }
        }
    }

    // Up / down (y-axis) (jumping etc.) movement.
    camera.Move('y', (playerMovement.y * playerMoveSpeed));

    // Get mouse cursor movement changes:
    mouse = input.getMouse();
    // If mouse has moved, spit it into console:
    if (mouse['x'] | mouse['y']) std::cout << "Mouse moved X: " << mouse['x'] << ", Y: " << mouse['y'] << std::endl;

    // Rotate camera
    camera.RotateX(mouse['x'] * lookSensitivity); // Look left/right
    camera.RotateY(mouse['y'] * lookSensitivity); // Look up/down

    // Mouse buttons (should be done with keyboard shortcuts?)
    if (mouse['l']) fire();
}


void drawGame(std::vector<std::shared_ptr<Shader>> &shader, std::vector<std::shared_ptr<Cube>> &gameworld, Window &window){
    glClearColor(0.0f, 0.15f, 0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto c : gameworld)
    {
        shader[0]->Update(c->t,camera);
        c->Draw();
    }
shader[0]->Bind();
    for (auto p : projectiles)
    {
        shader[1]->Update(p->t,camera);
        p->Draw();
    }
    shader[1]->Bind();

    window.Update();
}


void updateWorld(){

    // Move projectiles forward, set any that are too far away from player to dead:
    for (auto p : projectiles)
    {
        p->t.GetPos()+= p->t.GetForwards(); // Move forward.
        if (fabsf(p->t.GetPos().x) > 99 + fabsf(camera.GetPos().x) ||
            fabsf(p->t.GetPos().y) > 99 + fabsf(camera.GetPos().y) ||
            fabsf(p->t.GetPos().z) > 99 + fabsf(camera.GetPos().z)
        )
        {
            p->SetDead();
            std::cout << "Projectile removed because out of range of player, ";
            std::cout << "x: " << p->t.GetPos().x << ", ";
            std::cout << "y: " << p->t.GetPos().y << ", ";
            std::cout << "z: " << p->t.GetPos().z << "." << std::endl;
        }
    }

    pGravity(); // Make the player fall.

    // Detect collisions:
    for (auto p : projectiles)
    {
        for (auto c : gameworld)
        {
            if (isColliding(p->t.GetPos(), p->t.GetScale(), c->t.GetPos(), c->t.GetScale()))
            {
                // There was a collision and now the two things explode.
                std::cout << "COLLISION!" << std::endl;
                p->SetDead();
                c->SetDead();
            }
        }
    }

    // Remove dead projectiles:
    std::vector<std::shared_ptr<Cube>> tmpProjectiles;
    for (auto p : projectiles)
    {
        if (!p->IsDead()) tmpProjectiles.push_back(p);
    }
    projectiles.clear();
    projectiles = tmpProjectiles;

    // Remove dead cubes:
    std::vector<std::shared_ptr<Cube>> tmpCubes;
    for (auto c : gameworld)
    {
        if (!c->IsDead()) tmpCubes.push_back(c);
    }
    gameworld.clear();
    gameworld = tmpCubes;
}


int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(0); // Hide mouse cursor
    SDL_SetRelativeMouseMode(SDL_TRUE); // Capture mouse (prevents stuck when hitting window edge)
    Window window(960,720, "game");

    std::vector<std::shared_ptr<Shader>> shader;
    shader.push_back(std::make_shared<Shader>("./res/basicShader"));
    shader.push_back(std::make_shared<Shader>("./res/basicShader2"));

    std::cout << "BlockGame started!" << std::endl;

    level.Load(gameworld); // Load all the cubes!

    while(!window.IsClosed() && gameRunning)
    {

        handleInput();

        updateWorld();

        drawGame(shader, gameworld, window);

    }
    SDL_QUIT;
    return 0;
}
