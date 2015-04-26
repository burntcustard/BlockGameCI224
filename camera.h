#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

class Camera
{
    public:
        Camera()
        {
            _perspective = glm::perspective(70.0f, 800/600.0f, 0.01f, 500.0f);
            _cameraPosition = glm::vec3(0,0,0); // Position of camera in world space
            forward = glm::vec3(0,0,1); // The way the camera is looking, default is looking in Z direction
            up = glm::vec3(0,1,0); // Which way is up in relation to the camera
        }

	inline glm::mat4 GetViewProjection() const
	{
		return _perspective * glm::lookAt(_cameraPosition, _cameraPosition + forward, up);
	}

	void MoveForward(float amount)
	{
		_cameraPosition.x += forward.x * amount;
		_cameraPosition.z += forward.z * amount;
		std::cout << "New camera position: " << std::endl;
		std::cout << "X: " << _cameraPosition.x << std::endl;
		std::cout << "Y: " << _cameraPosition.y << std::endl;
		std::cout << "Z: " << _cameraPosition.z << std::endl;
	}

    inline glm::vec3& GetPos() {return _cameraPosition;}

	void MoveRight(float amount)
	{
	    glm::vec3 moved = glm::cross(up, forward) * amount;
		_cameraPosition.x += moved.x;
		_cameraPosition.z += moved.z;
	}

	void RotateY(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
		up = glm::normalize(glm::cross(forward, right));
	}

	void RotateX(float angle)
	{
	    // Rotate around the y axis (x,Y,z)
		glm::mat4 rotation = glm::rotate(angle, glm::vec3(0,-1,0));

		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
		up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	}

private:
	glm::mat4 _perspective;
	glm::vec3 _cameraPosition;
	glm::vec3 forward;
	glm::vec3 up;
};

#endif
