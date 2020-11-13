#include <stdio.h>
#include <glad\glad.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "Utility_OpenGL.h";

using namespace std;


std::string U_readFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

const char* U_getShaderSource(const char* filepath) {
	std::string shaderStr = U_readFile(filepath);
	
	const char* shaderSource = shaderStr.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &shaderSource, NULL);
	
	
	return shaderSource;
}

bool U_compileShader(unsigned int &vertexShader) {

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return success;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


GLFWwindow* initWindow(const unsigned int width, const unsigned int height) {
	// Intialize GLFW  ---------------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//tells to use the core profile:smaller subset of openGL features
	//such as no backward compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif

	// Create window object 
	// --------------------
	GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);


//Initialize GLAD  ---------------------------------------
// load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//here
	//glfwSetKeyCallback(window, key_callback); **
		// OpenGL Configuration
	// glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); **
	glEnable(GL_DEPTH_TEST);
	// glBlendFunct(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); **

	return window;
}

static void rotate(glm::vec3& inputvec, glm::vec3 rotation_axis, float theta, bool tonormalize)
{
	const float cos_theta = cos(theta);
	const float dot = glm::dot(inputvec, rotation_axis);
	glm::vec3 cross = glm::cross(inputvec, rotation_axis);

	inputvec.x *= cos_theta; inputvec.y *= cos_theta; inputvec.z *= cos_theta;
	inputvec.x += rotation_axis.x * dot * (float)(1.0 - cos_theta);
	inputvec.y += rotation_axis.y * dot * (float)(1.0 - cos_theta);
	inputvec.z += rotation_axis.z * dot * (float)(1.0 - cos_theta);

	inputvec.x -= cross.x * sin(theta);
	inputvec.y -= cross.y * sin(theta);
	inputvec.z -= cross.z * sin(theta);

	if (tonormalize) inputvec = glm::normalize(inputvec);
}