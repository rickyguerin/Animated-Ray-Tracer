#pragma once
#ifndef LIGHT_PROGRAM_H
#define LIGHT_PROGRAM_H

#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include "../Illumination/light.h"

struct LightFrame {
	// Time when this frame begins
	float timestamp;

	glm::vec3 position;
	glm::vec3 color;
};

class LightProgram {
private:
	// All keyframes from input file
	std::vector<LightFrame> frames;

public:
	// Constructor
	LightProgram(const std::string& filename);

	// Interpolate between frames to get the Camera at the given time
	Light getLight(const float time) const;
};

#endif