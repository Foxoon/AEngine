#include "myMassSpring.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "../configuration.h"

#include <vector>

myMassSpring::myMassSpring(unsigned int width, unsigned int height)
{
	unsigned int i, j;

	//Creating width*height particles.



	//Creating springs.
	double k = DEFAULT_K;


	//Giving color values.
	kd[0] = 0.8f;		kd[1] = 0.8f;		kd[2] = 0.8f;		kd[3] = 1.0f;

	computeNormals();
}

void myMassSpring::clearForces()
{
	for (size_t i = 0; i < particles.size(); i++)
		for (size_t j = 0; j < particles[i].size(); j++) {
		}

}

void myMassSpring::addForces()
{
	glm::vec3 gravity(0.0f, -DEFAULT_MASS*GRAVITY, 0.0f);



}

void myMassSpring::calculateNextPosition()
{
	for (size_t i = 0; i < particles.size(); i++)
		for (size_t j = 0; j < particles[i].size(); j++)
			particles[i][j].calculateNextPosition();
}

void myMassSpring::ballCollision(mySphere *s)
{
	glm::vec3 repulsiveForce;
	for (size_t i = 0; i < particles.size(); i++)
	{
		for (size_t j = 0; j < particles[i].size(); j++)
		{

		}
	}
}

void myMassSpring::groundCollision(float floor_y)
{
	float l;
	for (size_t i = 0; i < particles.size(); i++)
		for (size_t j = 0; j < particles[i].size(); j++)
		{
			l = (particles[i][j].position.y - floor_y);
			if (l < 0)
				//particles[i][j].position.y = floor_y;
				particles[i][j].movable = false;
		}
}

void myMassSpring::computeNormals()
{




}

void myMassSpring::drawSpring()
{
	/*
	for (size_t i = 0; i < particles.size() - 1; i++)
		for (size_t j = 0; j < particles[i].size() - 1; j++)
		{
			glNormal3fv(&particles[i][j].normal[0]);
			glVertex3fv(&particles[i][j].position[0]);
			glNormal3fv(&particles[i + 1][j].normal[0]);
			glVertex3fv(&particles[i + 1][j].position[0]);
			glNormal3fv(&particles[i + 1][j + 1].normal[0]);
			glVertex3fv(&particles[i + 1][j + 1].position[0]);

			glNormal3fv(&particles[i][j].normal[0]);
			glVertex3fv(&particles[i][j].position[0]);
			glNormal3fv(&particles[i + 1][j + 1].normal[0]);
			glVertex3fv(&particles[i + 1][j + 1].position[0]);
			glNormal3fv(&particles[i][j + 1].normal[0]);
			glVertex3fv(&particles[i][j + 1].position[0]);
		}
		*/
		glDrawArrays(GL_TRIANGLES, 0, particles.size());

	
}

myMassSpring::~myMassSpring()
{

}

