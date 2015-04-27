#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
    public:
        Camera();
        ~Camera();
        // GetViewProjection is the tricky one. Declared here, but not defined if it's
        // written in the .cpp, and it needs to be defined when the program starts for
        // shader.cpp Shader::Update to be able to use it.
        inline glm::mat4 GetViewProjection() const
        {
            return _perspective * glm::lookAt(cameraPosition, cameraPosition + _forward, up);
        }
        inline glm::vec3 GetPos();
        void Move(char direction, float amount);
        void RotateY(float angle);
        void RotateX(float angle);
    private:
        glm::mat4 _perspective;
        glm::vec3 cameraPosition;
        glm::vec3 _forward;
        glm::vec3 up;
};

#endif
