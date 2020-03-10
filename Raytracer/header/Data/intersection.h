#pragma once
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <glm/vec3.hpp>

struct Intersection {
	float omega;
	glm::vec3 point;
	glm::vec3 normal;
	glm::vec3 dest;
};

#endif