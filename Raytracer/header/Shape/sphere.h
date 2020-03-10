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
	glm::vec3 center;

	// Radius of Sphere at this time
	double radius;

public:
	// Constructor
	Sphere(IlluminationModel* illumination, const glm::vec3& position, const double radius);

	// Override from Shape
	virtual void transformToCameraSpace(const glm::mat4& cameraMatrix);
	virtual Intersection collision(const glm::vec3& ray) const;
};

#endif