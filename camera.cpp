#include "camera.h"

Camera::Camera()
{
    _perspective = glm::perspective(70.0f, 800/600.0f, 0.01f, 500.0f);
    cameraPosition = glm::vec3(0,0,0); // Position of camera in world space
    _forward = glm::vec3(0,0,1); // The way the camera is looking, default is looking in Z direction
    up = glm::vec3(0,1,0); // Which way is up in relation to the camera
}

Camera::~Camera() {}

/* Defined in camera.h instead, see note there.
inline glm::mat4 Camera::GetViewProjection() const
{
    return _perspective * glm::lookAt(cameraPosition, cameraPosition + _forward, up);
}
*/

inline glm::vec3 Camera::GetPos()
{
    return cameraPosition;
}

/**
 * Moves camera around.
 *
 * Performs "sideways" movement instead of "forward/back" because the sideways direction
 * is always parallel to the "ground" (Y axis 0), so it ends up going the correct speed
 * all the time. It wouldn't go the right speed if it was trying to go the direction
 * the camera's looking. Imagine the camera pointing 89deg up (nearly straight up),
 * it would try to go mostly upwards (which would be ignored - you can't fly!) but
 * only slightly forwards, giving the camera an exceptionally slow forwards movement speed.
 *
 * To go forwards & backwards (direction Z), the camera is rotated 90deg right, the
 * sideways movement performed, and then rotated back 90deg, giving the "illusion" of
 * forward & backward movement.
 */
void Camera::Move(char direction, float amount)
{
    if (direction == 'y')
    // Up / down (y-axis) (jumping etc.) movement.
    {
        cameraPosition.y += amount;
    }
    else
    // Sideways (x-axis & z-axis) (along the ground) movement.
    {
        if (direction == 'z') RotateX(90); // If trying to move forward/back in relation to camera
        // cross gets the "other" direction (not forward or up, so sideways)
        glm::vec3 moved = glm::cross(up, _forward) * amount; // Calc amount moved sideways.
        cameraPosition.x += moved.x; // Add the distance moved.
        cameraPosition.z += moved.z; //
        if (direction == 'z') RotateX(-90); // Rotate camera back. (Pretend you never rotated!)
    }
}

// Rotate camera left / right
void Camera::RotateY(float angle)
{
    glm::vec3 right = glm::normalize(glm::cross(up, _forward)); // Get sideways direction

    glm::vec3 tmpForward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(_forward, 0.0)));
    glm::vec3 tmpUp = glm::normalize(glm::cross(tmpForward, right));

    // Only set new rotation if UP (in relation to camera)
    // won't be digging into horizontal plane (no front flips!)
    if (tmpUp.y > 0)
    {
        _forward = tmpForward;
        up = tmpUp;
    }
}

// Rotate camera up / down
void Camera::RotateX(float angle)
{
    // Rotate around the y axis (x,Y,z) minus to make it rotate clockwise when looking from above.
    glm::mat4 rotation = glm::rotate(angle, glm::vec3(0,-1,0));

    _forward = glm::vec3(glm::normalize(rotation * glm::vec4(_forward, 0.0)));
    up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
}
