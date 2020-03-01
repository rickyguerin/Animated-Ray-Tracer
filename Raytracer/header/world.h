#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include "sphereProgram.h"

class World {
private:
	// All programs in the World
	std::vector<SphereProgram> programs;

	// Background color for the World
	glm::ivec4 backgroundColor;

public:
	// Constructor
	World(const glm::ivec4 & color);

	// Add a program to the World
	void addProgram(const SphereProgram & program);

	// Fire a ray into the world and get its color
	const glm::ivec4 trace(const glm::mat4 & cameraMatrix, const glm::vec3 & ray, const float time);
};

#endif
