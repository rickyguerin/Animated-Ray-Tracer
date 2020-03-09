#include "../header/world.h"
#include "../header/WorldProgram/sphereProgram.h"
#include "../header/WorldProgram/triangleProgram.h"
#include "../header/Shape/shape.h"

World::World(const glm::ivec4 & color) {
	backgroundColor = color;
}

World::~World() {
	for (const ShapeProgram * prog : programs) {
		delete prog;
	}
}

void World::addProgram(const std::string filename) {
	// Position of dot in name.sphere
	size_t sphereExt = filename.length() - 7;
	assert(sphereExt > 0);

	// File is .sphere
	if (filename.substr(sphereExt).compare(".sphere") == 0) {
		programs.push_back(new SphereProgram(filename));
		return;
	}

	// Position of dot in name.triangle
	size_t triangleExt = filename.length() - 9;
	assert(triangleExt > 0);

	// File is .triangle
	if (filename.substr(triangleExt).compare(".triangle") == 0) {
		programs.push_back(new TriangleProgram(filename));
		return;
	}
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