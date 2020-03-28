#include <glm/mat3x4.hpp>
#include "../../header/Math/catmullRom.h"

glm::vec3 interpolate(const float u, const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3) {

	// Deal with initial/final point not existing
	glm::vec3 first = p0;
	glm::vec3 last = p3;

	if (p0 == NULL_POINT) { first = p1; }
	if (p3 == NULL_POINT) { last = p2; }

	glm::vec4 U = glm::vec4 { pow(u, 3), pow(u, 2), u, 1 };

	glm::mat3x4 G =
		glm::mat3x4 {
			first.x, p1.x, p2.x, last.x,
			first.y, p1.y, p2.y, last.y,
			first.z, p1.z, p2.z, last.z
		};

	glm::mat3x4 C = basis * G;
	return U * C;
}