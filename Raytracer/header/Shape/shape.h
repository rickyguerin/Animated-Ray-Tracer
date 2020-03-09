#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>
#include "../Illumination/illuminationModel.h"

class Shape {
protected:
	// How this shape is shaded
	IlluminationModel * illumination;

	// Constructor
	Shape(IlluminationModel * illumination) {
		this->illumination = illumination;
	}

public:
	// Destructor
	virtual ~Shape() {};

	// Transform this Shape to move it into camera space
	virtual void transformToCameraSpace(const glm::mat4 & cameraMatrix) = 0;

	// Determine if a ray collides with this Shape
	virtual bool collision(const glm::vec3 & ray) const = 0;

	// Determine what color to return if a ray collision occurs
	glm::ivec4 illuminate() const {
		return illumination->illuminate();
	}
};

#endif