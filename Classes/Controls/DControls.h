#pragma once
#include <GLFW\glfw3.h>

#ifndef CAMERA
#define CAMERA
#include "../Camera/Camera.h";
#endif

class Camera;
class DControls
{
public:     
	DControls(const unsigned int width, const unsigned int height, Camera* camera);
	~DControls();

	
	void processInput(GLFWwindow* window);
	void mouse_callback(GLFWwindow* window, double x, double y);
	void scroll_callback(GLFWwindow* window, double yoffset);
	
	
private:
	bool firstMouse = true;
	float lastX;
	float lastY;
	Camera* camera;
};

