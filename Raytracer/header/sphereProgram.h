#pragma once
#ifndef SPHEREPROG_H
#define SPHEREPROG_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "../header/sphere.h"

// One keyframe from a Sphere input file
struct SphereFrame {
	// Time when this frame begins
	float timestamp;

	// Location of Sphere center at this time
	glm::vec3 position;

	// Color of Sphere at this time
	glm::ivec4 color;

	// Radius of Sphere at this time
	double radius;
};

class SphereProgram {
private:
	// All keyframes from input file
	std::vector<SphereFrame> frames;

public:
	// Constructor
	SphereProgram(const std::string filename);

	// Interpolate between frames to get the Sphere at the given time
	Sphere getSphere(const float time);
};

#endif