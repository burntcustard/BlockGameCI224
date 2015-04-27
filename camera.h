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

	inline glm::vec3& GetPos() {return _cameraPosition;}

    /**
     * Moves camera around.
     *
     * Performs "sideways" movement instead of "forward/back" because the sideways direction
     * is always parallel to the "ground" (Y axis 0), so it ends up going the correct speed
     * all the time. It wouldn't go the right speed if it was trying to go the direction
     * the camera's looking. Imagine the camera pointing 89deg up (nearly straight up),
     * it would try to go mostly upwards (which would be ignored - you can't fly!) but
     * only slightly forwards, giving the camera an exeptionally slow forwards movement speed.
     *
     * To go forwards & backwards (direction Z), the camera is rotated 90deg right, the
     * sideways movement performed, and then rotated back 90deg, giving the "illusion" of
     * forward & backward movement.
     */
	void Move(char direction, float amount)
	{
        if (direction == 'y')
        {
            _cameraPosition.y += amount;
        }
        else
        {
            if (direction == 'z') RotateX(90); // If trying to move forward/back, rotate camera 90deg right.
            // cross gets the "other" direction (not forward or up, so sideways)
            glm::vec3 moved = glm::cross(up, forward) * amount; // Calc amount moved sideways.
            _cameraPosition.x += moved.x; // Add the distance moved.
            _cameraPosition.z += moved.z; //
            if (direction == 'z') RotateX(-90); // Rotate camera back.
        }
	}

    // Side strafe movement
	void MoveX(float amount)
	{

	}

    // Rotate camera left / right
	void RotateY(float angle)
	{
        glm::vec3 right = glm::normalize(glm::cross(up, forward));

        glm::vec3 tmpForward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
        glm::vec3 tmpUp = glm::normalize(glm::cross(forward, right));

        // Only set new rotation if forward (in relation to camera)
        // is in between straight down and straight up (no front flips!)
        if (tmpForward.z > 0 && tmpForward.z < 2)
        {
            forward = tmpForward;
            up = tmpUp;
        }
	}

    // Rotate camera up / down
	void RotateX(float angle)
	{
	    // Rotate around the y axis (x,Y,z) minus to make it rotate clockwise when looking from above.
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
