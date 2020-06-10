#include "../../header/Shape/triangle.h"

Triangle::Triangle(IlluminationModel* illumination, const std::vector<glm::vec3>& vertices) : Shape(illumination) {
	this->vertices = vertices;
}

void Triangle::transformToCameraSpace(const glm::mat4& cameraMatrix) {
	for (int i = 0; i < 3; i++) {
		vertices[i] = cameraMatrix * glm::vec4(vertices[i], 1.0f);
	}
}

Intersection Triangle::collision(const Ray& ray) const {

	glm::vec3 e1 = vertices[1] - vertices[0];
	glm::vec3 e2 = vertices[2] - vertices[0];
	glm::vec3 T = ray.origin - vertices[0];
	glm::vec3 P = glm::cross(ray.direction, e2);
	glm::vec3 Q = glm::cross(T, e1);

	float bottom = glm::dot(P, e1);

	// Ray is parallel to Triangle
	if (bottom == 0) { return NULL_INTERSECTION; }

	glm::vec3 top {
		glm::dot(Q, e2),
		glm::dot(P, T),
		glm::dot(Q, ray.direction)
	};

	glm::vec3 bary = top / bottom;

	// Intersection is either outside Triangle or behind ray origin
	for (int i = 0; i < 3; i++) {
		if (bary[i] < 0) { return NULL_INTERSECTION; }
	}

	// Intersection is outside Triangle
	if (bary[1] + bary[2] > 1) { return NULL_INTERSECTION; }

	// Intersection is inside Triangle
	return Intersection{
		bary.x,
		ray.origin + ray.direction * bary.x,
		-glm::normalize(glm::cross(e1, e2)),
		ray.direction
	};
}