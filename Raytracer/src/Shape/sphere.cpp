#include <algorithm>

#include "../../header/Shape/sphere.h"

Sphere::Sphere(IlluminationModel* illumination, const glm::vec3& position, const double radius) : Shape(illumination) {
	this->center = position;
	this->radius = radius;
}

void Sphere::transformToCameraSpace(const glm::mat4& cameraMatrix) {
	center = cameraMatrix * glm::vec4(center, 1.0f);
}

Intersection Sphere::collision(const Ray& ray) const {

	glm::vec3 toCenter = ray.origin - center;

	double b = glm::dot(ray.direction, toCenter) * 2.0;
	double c = glm::dot(toCenter, toCenter) - pow(radius, 2);
	double disc = (b * b) - (4.0 * c);

	if (disc < 0.0) {
		return NULL_INTERSECTION;
	}

	double e = sqrt(disc);

	double minusRoot = (-b - e) / 2.0;
	double plusRoot = (-b + e) / 2.0;

	// Set omega to be the smallest positive root value
	float omega = std::min(minusRoot, plusRoot);
	if (omega < 0) { omega = std::max(minusRoot, plusRoot); }

	// If both roots are negative, return NULL
	if (omega < 0) { return NULL_INTERSECTION; }

	else {
		glm::vec3 point = ray.direction * omega;
		glm::vec3 normal = glm::normalize(point - center);

		return Intersection {
			omega,
			point,
			normal,
			ray.direction
		};
	}
}