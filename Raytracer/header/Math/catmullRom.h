#pragma once
#ifndef CATMULL_ROM_H
#define INTERSECTION_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

static const float tension = 0.5f;

static const glm::vec3 NULL_POINT = glm::vec3(9999.9f, 9999.9f, 9999.9f);

static const glm::mat4x4 basis =
	glm::mat4x4{
		-tension, 2 * tension, -tension, 0,
		3 * tension, -5 * tension, 0, 2 * tension,
		-3 * tension, 4 * tension, tension, 0,
		tension, -tension, 0, 0
	};

glm::vec3 interpolate(const float u, const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);

#endif