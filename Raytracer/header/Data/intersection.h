#pragma once
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <glm/vec3.hpp>

struct Intersection {
	float omega;
	glm::vec3 point;
	glm::vec3 normal;
	glm::vec3 ray;

	// Determine if this Intersection is NULL_INTERSECTION
	bool isNull() {
		return (omega == -1.0f);
	}
};

// Used to indicate that no intersection occurred
static const Intersection NULL_INTERSECTION {
	-1.0f, glm::vec3(-1.0f), glm::vec3(-1.0f), glm::vec3(-1.0f)
};

#endif