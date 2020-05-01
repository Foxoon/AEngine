#include "Light.h"


Light::Light()
{
	color = glm::vec3(2,31,230);
	brightness = 4.0f;
}

Light::Light(glm::vec3 color) {
	color = color;
}