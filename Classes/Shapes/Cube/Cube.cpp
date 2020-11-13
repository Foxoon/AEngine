#pragma once

#include "Cube.h"
#include <glad\glad.h>


Cube::Cube(glm::vec3 position, float size) {
	this->position = position;
	vertices = {};

}


void Cube::setVertices() {
	this->vertices = 
	{	
		// first face (top left, top right, bottom right, bottom left
		position.x - size / 2, position.y + size / 2, position.z - size / 2,
		position.x + size/2, position.y + size/2, position.z - size/2,
		position.x + size/2, position.y - size/2, position.z - size/2,
		position.x - size/2, position.y - size/2, position.z - size/2,

		//second face 

		position.x - size / 2, position.y + size / 2, position.z + size / 2,
		position.x + size / 2, position.y + size / 2, position.z + size / 2,
		position.x + size / 2, position.y - size / 2, position.z + size / 2,
		position.x - size / 2, position.y - size / 2, position.z + size / 2
	};
}

void Cube::Display() {
	//declaration Buffer and array objects
	unsigned int VBO, VAO;// EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	//reference
	//float* arr = &vertices[0];
	//	float* arr = vertices.data();  //copy
	float* arr = {};
	std::copy(vertices.begin(), vertices.end(), arr);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);
} 