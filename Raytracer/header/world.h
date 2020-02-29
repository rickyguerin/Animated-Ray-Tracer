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
	std::vector<Sphere> objects;

public:
	glm::ivec4 trace(Ray ray, double time);

	void add(std::string filename);

	void transformToCameraSpace(glm::mat4 cameraMatrix);
};

#endif
