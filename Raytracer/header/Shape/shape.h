#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "../Illumination/illuminationModel.h"
#include "../Math/intersection.h"
#include "../Math/ray.h"

class Shape {
protected:
	// Constructor
	Shape(IlluminationModel* illumination) {
		this->illumination = illumination;
		this->cameraToWorldMatrix = glm::mat4();
	}

public:
	// How this shape is shaded
	IlluminationModel* illumination;

	// Matrix to transform a point back to world space
	glm::mat4 cameraToWorldMatrix;

	// Destructor
	virtual ~Shape() {};

	// Transform this Shape to move it into camera space
	virtual void transformToCameraSpace(const glm::mat4& cameraMatrix) = 0;

	// Determine if a ray collides with this Shape
	virtual Intersection collision(const Ray& ray) const = 0;

	// Determine what color to return if a ray collision occurs
	glm::vec3 illuminate(Intersection intersection, const std::vector<Light>& lights, const bool shadow) const {
		return illumination->illuminate(intersection, lights, shadow);
	}
};

#endif