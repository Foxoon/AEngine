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

#ifndef UTILITY
#define UTILITY
#include "Classes/Utility/Utility_OpenGL.h";
#endif


#include "Classes/Shader/Shader.h"
#include "Classes/Camera/Camera.h"
#include "Classes/Light/Light.h"
#include "Classes/Controls/DControls.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Dependencies/stb/stb_image.h"
using namespace std;


void mouseCursorPosWrapper(GLFWwindow* window, double x, double y);
void mouseScrollWrapper(GLFWwindow* window, double x, double y);


// settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

//urlPath
const std::string shaderPath = "Shaders/";
// ---------  Time variables  -------------
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


	//move this 2 lines above main//
Camera* camera = new Camera();

static DControls* controls = new DControls(SCREEN_WIDTH, SCREEN_HEIGHT, camera);




int main()
{
	GLFWwindow* window = initWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	glfwSetCursorPosCallback(window, mouseCursorPosWrapper);
	glfwSetScrollCallback(window, mouseScrollWrapper);




	// build and compile our shader Program
	std::string vertexPathstr = shaderPath + "firstVertex.glsl";
	std::string fragPathstr = shaderPath + "firstFragment.glsl";
	const char* vertexPath = vertexPathstr.c_str();
	const char* fragPath = fragPathstr.c_str();

	Shader ourShader(vertexPath, fragPath);


	// set up vertex data (and buffer(s)) and configure vertex attributes
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

		controls->processInput(window);
		// -----

		//per frame  tick
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//  ---------- render
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

void mouseCursorPosWrapper(GLFWwindow* window, double x, double y) {
	if (controls) {
		controls->mouse_callback(window, x, y);
	}
}

void mouseScrollWrapper(GLFWwindow* window, double x, double y) {
	if (controls) {
		controls->scroll_callback(window, y);
	}
}

