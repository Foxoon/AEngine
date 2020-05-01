#pragma once
#include <glm/vec3.hpp> // glm::vec3


class Ambiant_Light
{
public:
	float strength;
	glm::vec3 color;
	Ambiant_Light(float strength, glm::vec3 color);


private:
	glm::vec3 getValue();

};

