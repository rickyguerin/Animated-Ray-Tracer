#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/glm.hpp>

static const double EPSILON = 0.001;

class Sphere {
private:
	// Location of Sphere center at this time
	glm::vec3 position;

	// Color of Sphere at this time
	glm::ivec4 color;

	// Radius of Sphere at this time
	double radius;

public:
	// Constructor
	Sphere(const glm::vec3 position, const glm::ivec4 color, const double radius);

	// Transform position to move this Sphere into camera space
	void transformToCameraSpace(glm::mat4 cameraMatrix);

	// Determine if a ray collides with this Sphere
	bool collision(glm::vec3 ray);

	// Determine what color to return if a ray collision occurs
	glm::ivec4 illuminate();
};

#endif