#include "ray.h"

Ray::Ray(glm::vec3 origin) {
	this->origin = origin;
	this->direction = glm::vec3(0, 0, 0);
}

Ray::Ray(glm::vec3 origin, glm::vec3 direction) {
	this->origin = origin;
	this->direction = direction;
}

glm::vec3 Ray::getOrigin() {
	return origin;
}

glm::vec3 Ray::getDirection() {
	return direction;
}

void Ray::setDirection(glm::vec3 direction) {
	this->direction = direction;
}