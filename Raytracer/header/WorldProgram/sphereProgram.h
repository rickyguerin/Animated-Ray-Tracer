#pragma once
#ifndef SPHEREPROG_H
#define SPHEREPROG_H

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "shapeProgram.h"

// One keyframe from a Sphere input file
struct SphereFrame {
	// Time when this frame begins
	float timestamp;

	// Shading of Sphere at this time
	IlluminationModel * illumination;

	// Location of Sphere center at this time
	glm::vec3 position;

	// Radius of Sphere at this time
	double radius;
};

class SphereProgram : public ShapeProgram {
private:
	// All keyframes from input file
	std::vector<SphereFrame> frames;

public:
	// Constructor
	SphereProgram(const std::string & filename);

	// Interpolate between frames to get the Sphere at the given time
	virtual Shape * getShape(const float time) const;
};

#endif