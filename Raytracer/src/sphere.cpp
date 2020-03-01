#include "../header/sphere.h"

Sphere::Sphere(const glm::vec3 position, const glm::ivec4 color, const double radius) {
	this->position = position;
	this->color = color;
	this->radius = radius;
}

void Sphere::transformToCameraSpace(glm::mat4 cameraMatrix) {
	position = cameraMatrix * glm::vec4(position, 1.0f);
}

bool Sphere::collision(glm::vec3 ray) {
	
	double a = glm::dot(ray, ray);
	double b = glm::dot(ray, -position) * 2.0;
	double c = glm::dot(-position, -position) - (radius * radius);
	double disc = (b * b) - (4.0 * a * c);

	if (disc < 0.0) {
		return false;
	}

	double e = sqrt(disc);
	double denom = 2.0 * a;

	double minusRoot = (-b - e) / denom;
	
	if (minusRoot > EPSILON) {
		return true;
	}

	double plusRoot = (-b + e) / denom;
	
	return plusRoot > EPSILON;
}

glm::ivec4 Sphere::illuminate() {
	return color;
}