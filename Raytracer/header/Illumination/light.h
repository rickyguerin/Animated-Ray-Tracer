#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

struct Light {
	glm::vec3 position;
	glm::vec3 color;

	void transformToCameraSpace(const glm::mat4& cameraMatrix);
};

#endif