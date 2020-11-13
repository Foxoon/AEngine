#pragma once
#include "../Shapes/Sphere/mySphere.h"
#include "../configuration.h"
#include "../Particle/myParticle.h"
#include "../Spring/mySpring.h"

#include <vector>

using namespace std;

class myMassSpring
{
public:
	std::vector< std::vector<myParticle> > particles;
	std::vector<mySpring> springs;

	glm::vec4 kd;

	myMassSpring(unsigned int width = DEFAULT_WIDTH, unsigned int height = DEFAULT_WIDTH);

	void clearForces();

	void addForces();

	void calculateNextPosition();

	void ballCollision(mySphere *s);

	void groundCollision(float floor_y);

	void computeNormals();

	void drawSpring();

	~myMassSpring();
};

