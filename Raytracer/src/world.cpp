#include "../header/world.h"
#include "../header/sphere.h"

World::World(const glm::ivec4 & color) {
	backgroundColor = color;
}

void World::addProgram(const SphereProgram & program) {
	programs.push_back(program);
}

const glm::ivec4 World::trace(const glm::mat4 & cameraMatrix, const glm::vec3 & ray, const float time) {
	for (int i = 0; i < programs.size(); i++) {
		Sphere sphere = programs[i].getSphere(time);
		sphere.transformToCameraSpace(cameraMatrix);

		if (sphere.collision(ray)) {
			return sphere.illuminate();
		}
	}

	return backgroundColor;
}