#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4

#include "../../Utility/Utility_OpenGL.h"
class Camera
{

public:


	glm::vec3 position;
	glm::vec3 upVector;
	glm::vec3 direction;
	glm::vec3 right;

	float yaw;
	float pitch;

	float speed = 2.5f;
	float sensitivity = 0.01f;
	float fov = 45.0f;


	Camera();
	Camera(glm::vec3 position, glm::vec3 upVector, glm::vec3 direction, float yaw , float pitch);
	~Camera();

	glm::mat4 GetViewMatrix();
	void processKeyboard(Camera_Movement direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset);
	void processMouseScroll(float offset);


private :
	void updateCameraVectors();
};

