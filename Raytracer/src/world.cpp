#include "../header/world.h"
#include "../header/sphereProgram.h"
#include "../header/triangleProgram.h"
#include "../header/shape.h"

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

	// File is .sphere
	if (filename.substr(sphereExt).compare(".sphere") == 0) {
		programs.push_back(new SphereProgram(filename));
		return;
	}

	// Position of dot in name.triangle
	size_t triangleExt = filename.length() - 9;

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