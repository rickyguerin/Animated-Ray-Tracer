#pragma once
#ifndef RAY_H
#define RAY_H

#include <glm/vec3.hpp>

class Ray {
private:
	glm::vec3 origin;
	glm::vec3 direction;

public:
	// Constructors
	Ray(glm::vec3 origin);
	Ray(glm::vec3 origin, glm::vec3 direction);

	// Accessors
	glm::vec3 getOrigin();
	glm::vec3 getDirection();

	// Mutator
	void setDirection(glm::vec3 direction);
};

#endif