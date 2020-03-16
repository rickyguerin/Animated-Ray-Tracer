#include <algorithm>

#include "../../header/Shape/sphere.h"

Sphere::Sphere(IlluminationModel* illumination, const glm::vec3& position, const double radius) : Shape(illumination) {
	this->center = position;
	this->radius = radius;
}

void Sphere::transformToCameraSpace(const glm::mat4& cameraMatrix) {
	center = cameraMatrix * glm::vec4(center, 1.0f);
}

Intersection Sphere::collision(const glm::vec3& ray) const {
	
	double a = glm::dot(ray, ray);
	double b = glm::dot(ray, -center) * 2.0;
	double c = glm::dot(-center, -center) - (radius * radius);
	double disc = (b * b) - (4.0 * a * c);

	if (disc < 0.0) {
		return NULL_INTERSECTION;
	}

	double e = sqrt(disc);
	double denom = 2.0 * a;

	double minusRoot = (-b - e) / denom;
	double plusRoot = (-b + e) / denom;

	// Set omega to be the smallest positive root value
	float omega = std::min(minusRoot, plusRoot);
	if (omega < 0) { omega = std::max(minusRoot, plusRoot); }

	// If both roots are negative, return NULL
	if (omega < 0) { return NULL_INTERSECTION; }

	else {
		glm::vec3 point = ray * omega;
		glm::vec3 normal = glm::normalize(point - center);

		return Intersection {
			omega,
			point,
			normal,
			ray
		};
	}
}