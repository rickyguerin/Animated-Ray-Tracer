#include "../header/world.h"
#include "../header/sphere.h"

World::World(const glm::ivec4 & color) {
	backgroundColor = color;
}

World::~World() {
	for (auto prog : programs) {
		delete prog;
	}
}

void World::addProgram(const ShapeProgram * program) {
	programs.push_back(program);
}

glm::ivec4 World::trace(const glm::mat4 & cameraMatrix, const glm::vec3 & ray, const float time) const {
	glm::ivec4 color;

	for (int i = 0; i < programs.size(); i++) {
		Shape* shape = programs[i]->getShape(time);
		shape->transformToCameraSpace(cameraMatrix);

		bool collided = shape->collision(ray);

		if (collided) {
			color = shape->illuminate();
		}

		delete shape;

		if (collided) {
			return color;
		}
	}

	return backgroundColor;
}