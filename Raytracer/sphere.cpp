#include <glm/glm.hpp>
#include "sphere.h"

Sphere::Sphere(glm::vec3 pos, float radius) {
	this->pos = pos;
	this->radius = radius;
}

glm::vec3 Sphere::getPos() {
	return pos;
}

float Sphere::getRadius() {
	return radius;
}

bool Sphere::collision(Ray ray) {
	glm::vec3 rayDir = ray.getDirection();
	glm::vec3 oc = ray.getOrigin() - pos;

	double b = glm::dot(rayDir, oc) * 2.0;
	double c = glm::dot(oc, oc) - (radius * radius);
	double disc = (b * b) - (4.0 * c);

	if (disc < 0.0) {
		return false;
	}

	double minusRoot = (-b - sqrt(disc)) / 2.0;
	
	if (minusRoot > 0) {
		return true;
	}

	double plusRoot = (-b + sqrt(disc)) / 2.0;
	
	return plusRoot > 0;
}