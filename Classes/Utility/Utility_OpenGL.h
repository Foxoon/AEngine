#pragma once

#include <string>
#include <iostream>
#include <GLFW\glfw3.h>


std::string U_readFile(const char *filePath);

const char* U_getShaderSource(const char* filepath);
bool U_compileShader(unsigned int &vertexShader);
template <typename T> void U_readPointer(T var);
GLFWwindow* initWindow(const unsigned int width, const unsigned int height);

template <typename T> void U_readPointer(T var) {
	printf("\n");
	std::cout << "Adress of the pointer : " << var << std::endl;
	std::cout << "Value of the pointer : " << *var << std::endl;

}

static void rotate(glm::vec3& inputvec, glm::vec3 rotation_axis, float theta, bool tonormalize = false);
