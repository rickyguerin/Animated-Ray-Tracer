#include <glm/glm.hpp>
#include "sphere.h"
#include "ray.h"

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

	double t;
	double a = glm::dot(rayDir, rayDir);
	double b = glm::dot(rayDir, oc) * 2.0;
	double c = glm::dot(oc, oc) - (radius * radius);
	double disc = (b * b) - (4.0 * a * b);

	if (disc < 0.0) {
		return false;
	}

	double e = sqrt(disc);
	double denom = 2.0 * a;
	t = (-b - e) / denom;

	return t > 0.0001;
}