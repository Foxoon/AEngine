#pragma once
#include "../../Utility/Utility_OpenGL.h"
#include <glm/vec3.hpp> // glm::vec3

class Light
{

private :
	glm::vec3 direction;
	glm::vec3 color;
	float brightness;


public:
	Light();
	Light(glm::vec3 color);
	~Light();
};