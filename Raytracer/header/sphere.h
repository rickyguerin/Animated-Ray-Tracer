#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/glm.hpp>

#include "shape.h"

static const double EPSILON = 0.001;

class Sphere : public Shape {
private:
	// Location of Sphere center at this time
	glm::vec3 position;

	// Radius of Sphere at this time
	double radius;

public:
	// Constructor
	Sphere(const glm::vec3 & position, const glm::ivec4 & color, const double radius);

	// Override from Shape
	virtual void transformToCameraSpace(const glm::mat4 & cameraMatrix);
	virtual const bool collision(const glm::vec3 & ray);
	virtual const glm::ivec4 illuminate();
};

#endif