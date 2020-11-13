#pragma once
#include <glm/vec3.hpp> // glm::vec3
#include "../Shape.h"
#include <vector>

class Cube 
{
public:
	Cube(glm::vec3 position, float size);
	~Cube();
	void Display();
private:
	std::vector<float> vertices;

	float size;
	glm::vec3 position;
	void setVertices();
};
