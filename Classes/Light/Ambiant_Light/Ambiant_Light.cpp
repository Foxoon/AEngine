#include "Ambiant_Light.h"

Ambiant_Light::Ambiant_Light(float strength, glm::vec3 color) {
	strength = strength;
	color = color;
}

glm::vec3 Ambiant_Light::getValue() {
	return strength * color;
}