#include "DControls.h"


#ifndef CAMERA
#define CAMERA
#include "../Camera/Camera.h";
#endif




extern float deltaTime;



DControls::DControls(const unsigned int width, const unsigned int height, Camera* camera){
	this->lastX = width / 2.0f;
	this->lastY = height / 2.0f;
	this->camera = camera;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void DControls::processInput(GLFWwindow* window)
{
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->processKeyboard(FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->processKeyboard(BACKWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->processKeyboard(LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->processKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->processKeyboard(UPWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		camera->processKeyboard(DOWNWARD, deltaTime);


	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->processKeyboard(ROTATE_LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera->processKeyboard(ROTATE_RIGHT, deltaTime);


	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		camera->processKeyboard(ROTATE_UP, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		camera->processKeyboard(ROTATE_DOWN, deltaTime);

}



void DControls::mouse_callback(GLFWwindow* window, double x, double y) {
	
	if(DControls::firstMouse) // this bool variable is initially set to true
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
		firstMouse = false;
	}

	float xoffset = x - lastX;
	float yoffset = lastY - y; // reversed since y-coordinates range from bottom to top
	lastX = x;
	lastY = y;

	camera->processMouseMovement(xoffset, yoffset);


}

void DControls::scroll_callback(GLFWwindow* window, double yoffset)
{
	camera->processMouseScroll(yoffset);
}


DControls::~DControls() {

}