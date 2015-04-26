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
        Cube();

        void Draw();
        Transform t;
        Cube(const Cube& other);
        virtual ~Cube();
    protected:
    private:

        void operator=(const Cube& other);

        enum
        {
            POSITION_VB,
            NUM_BUFFERS
        };

        GLuint _vertexArrayObject;
        GLuint _vetexArrayBuffers[NUM_BUFFERS];
        unsigned int _drawCount;
};

#endif // MESH_H
