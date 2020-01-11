#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"

struct SphereFrame {
	double timestamp;
	glm::vec3 position;
	double radius;
};

class Sphere {
private:
	glm::vec3 pos;
	double radius;

public:
	Sphere(glm::vec3 pos, float radius);

	glm::vec3 getPos();

	float getRadius();

	bool collision(Ray ray, double time);
};

#endif