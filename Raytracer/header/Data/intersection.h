#pragma once
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <glm/vec3.hpp>

struct Intersection {
	float omega;
	glm::vec3 point;
	glm::vec3 normal;

	// Determine if this Intersection is NULL_INTERSECTION
	bool isNull() {
		return (omega == -1.0f);
	}
};

#endif