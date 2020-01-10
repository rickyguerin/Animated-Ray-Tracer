#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <glm/vec3.hpp>
#include "sphere.h"
#include "ray.h"

class World {
private:
	std::vector<Sphere> objects;

public:
	World(std::vector<Sphere> objects);

	glm::vec3 trace(Ray ray);
};

#endif
