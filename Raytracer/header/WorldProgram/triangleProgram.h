#pragma once
#ifndef TRIANGLEPROG_H
#define TRIANGLEPROG_H

#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include "shapeProgram.h"

// One keyframe from a Sphere input file
struct TriangleFrame {
	// Time when this frame begins
	float timestamp;

	// Shading of Triangle at this time
	IlluminationModel* illumination;

	// Vertices of Triangle in clockwise order at this time
	std::vector<glm::vec3> vertices;
};

class TriangleProgram : public ShapeProgram {
private:
	// All keyframes from input file
	std::vector<TriangleFrame> frames;

public:
	// Constructor
	TriangleProgram(const std::string& filename);

	// Interpolate between frames to get the Sphere at the given time
	virtual Shape* getShape(const float time) const;
};

#endif