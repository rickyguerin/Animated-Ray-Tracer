#pragma once
#ifndef CAMERAPROG_H
#define CAMERAPROG_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "camera.h"

struct CameraFrame {
	// Time when this frame begins
	float timestamp;

	// Orientation in world space
	glm::vec3 eye;
	glm::vec3 lookat;
	glm::vec3 up;

	// Film plane parameters
	float focalLength;
	float canvasWidth;
	float canvasHeight;
};

class CameraProgram {
private:
	// All keyframes from input file
	std::vector<CameraFrame> frames;

public:
	// Constructor
	CameraProgram(const std::string & filename);

	// Interpolate between frames to get the Camera at the given time
	Camera getCamera(const float time) const;
};

#endif