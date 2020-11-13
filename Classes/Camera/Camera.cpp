#include "Camera.h"

Camera::Camera()
{
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	direction = glm::vec3(0.0f, 0.0f, -1.0f);
	yaw = -90.0f;
	pitch = 0.0f;

}

Camera::Camera(glm::vec3 position, glm::vec3 upVector, glm::vec3 direction, float yaw, float pitch)
{
	position = position;
	upVector = upVector;
	direction = direction;
	yaw = yaw;
	pitch = pitch;
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(position, position + direction, upVector);
}


void Camera::processKeyboard(Camera_Movement movement, float deltaTime)
{
	updateCameraVectors();
	float velocity = speed * deltaTime;

	if (movement == LEFT) {
		position -= right * velocity;
		position.y = 0;
	}
		
	if (movement == RIGHT) {
		position += right * velocity;
		position.y = 0;
	}
	if (movement == FORWARD) {
		position += direction * velocity;
		position.y = 0;
	}
	if (movement == BACKWARD) {
		position -= direction * velocity;
		position.y = 0;
	}

	if (movement == UPWARD)
		position += upVector * velocity;

	if (movement == DOWNWARD)
		position -= upVector * velocity;
	if (movement == ROTATE_LEFT) {
		yaw -= 0.05;
		direction.x = cos(glm::radians(yaw)); // Note that we convert the angle to radians first
	}
	if (movement == ROTATE_RIGHT) {
		yaw += 0.05;
		direction.x = cos(glm::radians(yaw)); // Note that we convert the angle to radians first
	}
	if (movement == ROTATE_UP) {
		pitch += 0.05;
		direction.y = sin(glm::radians(pitch));
	}
	if (movement == ROTATE_DOWN) {
		pitch -= 0.05;
		direction.y = sin(glm::radians(pitch));
	}
}


void Camera::processMouseMovement(float xoffset, float yoffset) {

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	updateCameraVectors();
}

void Camera::processMouseScroll(float offset)
{
	float fovMax = 45.0f;

	if (fov >= 1.0f && fov <= fovMax)
		fov -= offset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= fovMax)
		fov = fovMax;
}


//TODO
void Camera::updateCameraVectors()
{
	// Calculate the new Front vector


	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(direction);

	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(direction, upVector));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	upVector = glm::normalize(glm::cross(right, direction));
}

Camera::~Camera()
{
}


