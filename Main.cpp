#pragma once

#include <stdio.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

//matrix operations libraries.
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>



#include <iostream>
#include "Utility/Utility_OpenGL.h"
#include "Classes/Shader/Shader.h"
#include "Classes/Camera/Camera.h"



#define STB_IMAGE_IMPLEMENTATION
#include "Dependencies/stb/stb_image.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double x, double y);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


// settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

//urlPath
const std::string shaderPath = "Shaders/";


// ---------   PROGRAM  -------------
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;


bool firstMouse = true;

Camera* camera = new Camera();

int main()
{

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
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//focus on the window
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//Initialize GLAD  ---------------------------------------
	// load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader Program

	// ------------------------------------
	std::string vertexPathstr = shaderPath + "firstVertex.glsl";
	std::string fragPathstr = shaderPath + "firstFragment.glsl";
	const char* vertexPath = vertexPathstr.c_str();
	const char* fragPath = fragPathstr.c_str();


	Shader ourShader(vertexPath, fragPath);


	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------



	float vertices[] = {
		//face 1
		0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.0f, -0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, -0.5f, 1.0f, 0.0f,

		//face 2
		0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.0f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,  0.0f, 0.0f,

		//face 3
		0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.0f, 0.5f,  1.0f, 0.0f,
		-0.5f, 0.0f, 0.5f, 0.0f, 0.0f,

		//face 4
		0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.0f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f, 0.0f, 0.0f,

		//face 5
		-0.5f, 0.0f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.0f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.0f, -0.5f, 0.0f, 0.0f,

		//face 6
		0.5f, 0.0f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.0f, 0.5f,  1.0f, 0.0f,
		-0.5f, 0.0f, 0.5f, 0.0f, 0.0f,


	};

	/*
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	*/


	//declaration Buffer and array objects
	unsigned int VBO, VAO;// EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// load and create a texture   ---------------------------------------
	unsigned int texture1;

	// texture 1   ---------------------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load("Ressources/Images/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
	// either set it manually like so:
	ourShader.setInt("texture1", 0);


	//camera 



	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input

		processInput(window);
		// -----

		//per frame  tick
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;



		//  ---------- render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ---------- bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		ourShader.use();

		//Transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera->fov), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1f, 100.0f);

		//uniforms
		ourShader.setMat4("projection", projection);
		
		//camera
		//TODO BUG with camera->GetVIewMatrix
		//glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);

		glm::mat4 view = camera->GetViewMatrix();
		ourShader.setMat4("view", view);


		// render container
		glBindVertexArray(VAO);

		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		ourShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
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

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		camera->processKeyboard(DOWNWARD, deltaTime);


	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->processKeyboard(ROTATE_LEFT, deltaTime);
	
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera->processKeyboard(ROTATE_RIGHT, deltaTime);

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double x, double y) {


	if (firstMouse) // this bool variable is initially set to true
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	float xoffset = x - lastX;
	float yoffset = lastY - y; // reversed since y-coordinates range from bottom to top
	lastX = x;
	lastY = y;

	camera->processMouseMovement(xoffset, yoffset);


}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->processMouseScroll(yoffset);
}


