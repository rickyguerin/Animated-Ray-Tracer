#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>

class Shape {
protected:
	// Color
	glm::ivec4 color;

	// Constructor
	Shape(const glm::ivec4 & color) {
		this->color = color;
	}

public:
	// Transform this Shape to move it into camera space
	virtual void transformToCameraSpace(const glm::mat4 & cameraMatrix) = 0;

	// Determine if a ray collides with this Shape
	virtual bool collision(const glm::vec3 & ray) const = 0;

	// Determine what color to return if a ray collision occurs
	virtual glm::ivec4 illuminate() const = 0;
};

#endif