#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include "sphere.h"
#include "ray.h"

class World {
private:
	// All objects in the World
	std::vector<Sphere> objects;

	// Background color for the World
	glm::ivec4 backgroundColor;

public:
	// Constructor
	World(glm::ivec4 color);

	// Fire a ray into the world and get its color
	glm::ivec4 trace(Ray ray, double time);

	// Read one object file and add that object to the world
	void add(std::string filename);

	// Edit every object to move it into camera space
	void transformToCameraSpace(glm::mat4 cameraMatrix);
};

#endif
