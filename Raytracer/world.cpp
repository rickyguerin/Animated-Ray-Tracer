#include "world.h"

World::World(std::vector<Sphere> objects) {
	this->objects = objects;
}

glm::ivec4 World::trace(Ray ray) {

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].collision(ray)) {
			return glm::ivec4(255, 0, 0, 255);
		}
	}

	if (double(rand()) / (double(RAND_MAX) + 1.0) < 0.0005) {
		return glm::ivec4(255, 255, 255, 255);
	}
	else {
		return glm::ivec4(0, 0, 0, 255);
	}
}