#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include "shapeProgram.h"

class World {
private:
	// All programs in the World
	std::vector<const ShapeProgram *> programs;

	// Background color for the World
	glm::ivec4 backgroundColor;

public:
	// Constructor
	World(const glm::ivec4 & color);

	// Destructor
	~World();

	// Add a program to the World
	void addProgram(const ShapeProgram * program);

	// Fire a ray into the world and get its color
	const glm::ivec4 trace(const glm::mat4 & cameraMatrix, const glm::vec3 & ray, const float time);
};

#endif
