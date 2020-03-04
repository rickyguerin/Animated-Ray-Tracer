#include "../header/triangle.h"

Triangle::Triangle(const std::vector<glm::vec3> & vertices, const glm::ivec4 & color) : Shape(color) {
	this->vertices = vertices;
}

void Triangle::transformToCameraSpace(const glm::mat4 & cameraMatrix) {
	for (int i = 0; i < 3; i++) {
		vertices[i] = cameraMatrix * glm::vec4(vertices[i], 1.0f);
	}
}

const bool Triangle::collision(const glm::vec3 & ray) {
	return false;
}

const glm::ivec4 Triangle::illuminate() {
	return color;
}