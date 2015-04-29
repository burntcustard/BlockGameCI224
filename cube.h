#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "transform.h"


class Vertex
{
    public:
        Vertex(const glm::vec3& pos)
        {
            this->pos =pos;
        }
    private:
        glm::vec3 pos;
};

class Cube
{
    public:
        Cube(float x, float y, float z);

        void Draw();
        Transform t;
        Cube(const Cube& other);
        bool IsDead();
        void SetDead();
        virtual ~Cube();
    protected:
    private:

        void operator=(const Cube& other);
        bool dead;
        glm::vec3 _forward;
        enum
        {
            POSITION_VB,
            NUM_BUFFERS
        };

        // Array of vertexes that make up the cube. Stored in GPU.
        GLuint vertexArrayObject;

        // These will probably be 0, used for error checking and making related values more readable.
        GLint coord3d, color;

        GLuint _vetexArrayBuffers[NUM_BUFFERS];
        uint8_t numVerticies;
};

#endif // MESH_H
