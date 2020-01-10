#include "world.h"

World::World(std::vector<Sphere> objects) {
	this->objects = objects;
}

glm::vec3 World::trace(Ray ray) {
	return glm::vec3(0, 0, 0);
}