#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
    public:
        Camera(glm::vec3 &playerSize);
        ~Camera();
        // inline functions are tricky. Declared here, but not defined if it's
        // written in the .cpp, and it needs to be defined when the program starts for
        // shader.cpp Shader::Update to be able to use it.
        inline glm::mat4 GetViewProjection() const
        {
            return _perspective * glm::lookAt(cameraPosition + pOffset, cameraPosition + pOffset + _forward, up);
        }
        inline glm::vec3 GetPos()
        {
            return cameraPosition;
        }
        inline glm::vec3 GetForward()
        {
            return _forward;
        }
        inline double getVelocityY(){
            return yVelocity;
        }
        double yVelocity;
        void Move(char direction, float amount);
        void RotateY(float angle);
        void RotateX(float angle);
        void Jump();
    private:
        glm::mat4 _perspective;
        glm::vec3 pOffset;
        glm::vec3 cameraPosition;
        glm::vec3 _forward;
        glm::vec3 up;

};

#endif
