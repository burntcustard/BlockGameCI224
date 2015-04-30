#include "cube.h"

Cube::Cube(float x, float y, float z)
{
    dead = false;
    GLfloat vaoCube[] = {

	-0.5,0.5,0.5, 		  //  0.0, 1.0, 0.0,
        0.5,0.5,0.5, 		//0.0, 1.0, 0.0,
        -0.5,-0.5,0.5, 	//	0.0, 1.0, 0.0,
        0.5,0.5,0.5, 	//	0.0, 1.0, 0.0,
        -0.5,-0.5,0.5, 	//0.0, 1.0, 0.0,
        0.5,-0.5,0.5, 		//0, 1.0, 0.0,

        -0.5,0.5,-0.5,//	0.0, 1.0, 0.0,
        0.5,0.5,-0.5, 	//	0.0, 1.0, 0.0,
        -0.5,-0.5,-0.5, //		0.0, 1.0, 0.0,
        0.5,0.5,-0.5, 	//	0.0, 1.0, 0.0,
        -0.5,-0.5,-0.5, //		0.0, 1.0, 0.0,
        0.5,-0.5,-0.5, 	//	0.0, 1.0, 0.0,

        0.5,0.5,0.5, 	//	0.0, 1.0, 0.0,
        0.5,-0.5,0.5, 	//	0.0, 1.0, 0.0,
        0.5,0.5,-0.5, 	//	0.0, 1.0, 0.0,
        -0.5,0.5,0.5, 	//	0.0, 1.0, 0.0,
        -0.5,-0.5,0.5, 	//	0.0, 1.0, 0.0,
        -0.5,0.5,-0.5, 	//	0.0, 1.0, 0.0,

        -0.5,-0.5,0.5, 	//	0.0, 1.0, 0.0,
        -0.5,0.5,-0.5, 	//	0.0, 1.0, 0.0,
        -0.5,-0.5,-0.5, //		0.0, 1.0, 0.0,
        0.5,-0.5,0.5, 	//	0.0, 1.0, 0.0,
        0.5,0.5,-0.5, 	//	0.0, 1.0, 0.0,
        0.5,-0.5,-0.5, 	//	0.0, 1.0, 0.0,

        -0.5,0.5,0.5, 	//	0.0, 1.0, 0.0,
        0.5,0.5,0.5, 	//	0.0, 1.0, 0.0,
        0.5,0.5,-0.5, 	//	0.0, 1.0, 0.0,
        -0.5,-0.5,0.5, 	//	0.0, 1.0, 0.0,
        0.5,-0.5,0.5, 	//	0.0, 1.0, 0.0,
        0.5,-0.5,-0.5, 	//	0.0, 1.0, 0.0,

        -0.5,0.5,0.5, 	//	0.0, 1.0, 0.0,
        -0.5,0.5,-0.5, 	//	0.0, 1.0, 0.0,
        0.5,0.5,-0.5, 	//	0.0, 1.0, 0.0,
        -0.5,-0.5,0.5, 	//	0.0, 1.0, 0.0,
        -0.5,-0.5,-0.5, //		0.0, 1.0, 0.0,
        0.5,-0.5,-0.5, 	//	0.0, 1.0, 0.0,
    };

    // Number of points in space that make up the cube. Max 255 (uint8_t).
    numVerticies = sizeof(vaoCube) / sizeof(vaoCube[1]);

    // Create (Generate) one vertex array data buffer, & make it the current active buffer:
    glGenVertexArrays(1, &vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayObject);
    // Push vertices to data buffer:
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vaoCube), // Buffer length.
        vaoCube,         // Vertices being put in buffer (the cube).
        GL_STATIC_DRAW   // Tells GPU to keep a copy of the buffer in it's memory.
    );

    glEnableVertexAttribArray(coord3d);

    glVertexAttribPointer(
        coord3d,                      // Attribute (must match value in glEnableVertexAttribArray.
        3,                            // Number of elements per vertex (x,y,x coords).
        GL_FLOAT,                     // Type of element.
        GL_FALSE,                     // Normalized? (0 or 1).
        3 * sizeof(GLfloat),                            // No extra data between each position.
        0 // Array buffer offset. (Size of the color data)
    );

/*
    // Color:
glEnableVertexAttribArray(v_color);
    glVertexAttribPointer(
        v_color,                        // Attribute (must match value in glEnableVertexAttribArray.
        3,                            // Number of elements per vertex (r,g,b)
        GL_FLOAT,                     // Type of element.
        GL_FALSE,                     // Normalized? (0 or 1).
        3 * sizeof(GLfloat),          // Next color appears every 0 (i.e. never)
        (GLvoid*) (3 * sizeof(GLfloat))  // Offset of first element
    );

    */
    t.GetPos()=glm::vec3(x,y,z);
    t.GetForwards()=glm::vec3(0,0,0);

}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &vertexArrayObject);
}

void Cube::Draw()
{
    // Draw the triangles:
    glDrawArrays(GL_TRIANGLES, 0, numVerticies);

    // Clear stuff so that other things can be drawn? Memory saved? Not needed in modern openGL?
    //glBindVertexArray(0);
    //glBindVertexArray(vertexArrayObject);
}

void Cube::SetDead()
{
    dead = true;
}

bool Cube::IsDead()
{
    return dead;
}


