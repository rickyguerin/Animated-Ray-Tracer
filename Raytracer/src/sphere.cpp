#include <glm/glm.hpp>
#include "../header/sphere.h"

void Sphere::addFrame(SphereFrame frame) {
	frames.push_back(frame);
}

unsigned Sphere::getCurrentFrame(double time) {

	int i = 0;

	for (i; i < frames.size() - 1; i++) {
		if (time <= frames[i + 1].timestamp) {
			return i;
		}
	}

	return i;
}

glm::vec3 Sphere::getPos(unsigned frame, double time) {
	return frames[frame].position;
}

double Sphere::getRadius(unsigned frame, double time) {
	return frames[frame].radius;
}

bool Sphere::collision(Ray ray, double time) {

	unsigned frame = getCurrentFrame(time);

	glm::vec3 pos = getPos(frame, time);
	double radius = getRadius(frame, time);

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