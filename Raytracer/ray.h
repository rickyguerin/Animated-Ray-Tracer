#pragma once
#ifndef RAY_H
#define RAY_H

class Ray {
private:
	glm::vec3 origin;
	glm::vec3 direction;

public:
	Ray(glm::vec3 origin);

	Ray(glm::vec3 origin, glm::vec3 direction);

	glm::vec3 getOrigin();

	glm::vec3 getDirection();

	void setDirection(glm::vec3 direction);
};

#endif