#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <glm/glm.hpp>

#include "shape.h"

class Triangle : public Shape {
private:
	// Vertices of Triangle in clockwise order
	std::vector<glm::vec3> vertices;

public:
	// Constructor
	Triangle(std::vector<glm::vec3> & vertices, const glm::ivec4 & color);

	// Override from Shape
	virtual void transformToCameraSpace(const glm::mat4 & cameraMatrix);
	virtual const bool collision(const glm::vec3 & ray);
	virtual const glm::ivec4 illuminate();
};

#endif