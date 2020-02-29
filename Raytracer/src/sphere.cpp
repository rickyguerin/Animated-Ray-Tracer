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

	if (frame == frames.size() - 1) {
		return frames[frame].position;
	}

	else {
		double t = (time - frames[frame].timestamp) / (frames[frame + 1].timestamp - frames[frame].timestamp);
		return glm::mix(frames[frame].position, frames[frame + 1].position, t);
	}
}

double Sphere::getRadius(unsigned frame, double time) {

	if (frame == frames.size() - 1) {
		return frames[frame].radius;
	}

	else {
		double t = (time - frames[frame].timestamp) / (frames[frame + 1].timestamp - frames[frame].timestamp);
		return glm::mix(frames[frame].radius, frames[frame + 1].radius, t);
	}
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

void Sphere::transformToCameraSpace(glm::mat4 cameraMatrix) {
	for (int i = 0; i < frames.size(); i++) {
		frames[i].position = cameraMatrix * glm::vec4(frames[i].position, 1.0f);
	}
}