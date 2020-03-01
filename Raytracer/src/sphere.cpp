#include "../header/sphere.h"

void Sphere::addFrame(SphereFrame frame) {
	frames.push_back(frame);
}

unsigned Sphere::getCurrentFrame(float time) {

	int i = 0;

	for (i; i < frames.size() - 1; i++) {
		if (time <= frames[i + 1].timestamp) {
			return i;
		}
	}

	return i;
}

glm::vec3 Sphere::getPos(unsigned frame, float time) {

	if (frame == frames.size() - 1) {
		return frames[frame].position;
	}

	else {
		double t = (time - frames[frame].timestamp) / (frames[frame + 1].timestamp - frames[frame].timestamp);
		return glm::mix(frames[frame].position, frames[frame + 1].position, t);
	}
}

glm::ivec4 Sphere::getColor(unsigned frame, float time) {

	if (frame == frames.size() - 1) {
		return frames[frame].color;
	}

	else {
		double t = (time - frames[frame].timestamp) / (frames[frame + 1].timestamp - frames[frame].timestamp);
		return glm::mix(frames[frame].color, frames[frame + 1].color, t);
	}
}

float Sphere::getRadius(unsigned frame, float time) {

	if (frame == frames.size() - 1) {
		return frames[frame].radius;
	}

	else {
		double t = (time - frames[frame].timestamp) / (frames[frame + 1].timestamp - frames[frame].timestamp);
		return glm::mix(frames[frame].radius, frames[frame + 1].radius, t);
	}
}

bool Sphere::collision(glm::vec3 ray, float time) {

	unsigned frame = getCurrentFrame(time);
	glm::vec3 pos = getPos(frame, time);
	double radius = getRadius(frame, time);

	double a = glm::dot(ray, ray);
	double b = glm::dot(ray, -pos) * 2.0;
	double c = glm::dot(-pos, -pos) - (radius * radius);
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

glm::ivec4 Sphere::illuminate(float time) {
	unsigned frame = getCurrentFrame(time);
	return getColor(frame, time);
}

void Sphere::transformToCameraSpace(glm::mat4 cameraMatrix) {
	for (int i = 0; i < frames.size(); i++) {
		frames[i].position = cameraMatrix * glm::vec4(frames[i].position, 1.0f);
	}
}