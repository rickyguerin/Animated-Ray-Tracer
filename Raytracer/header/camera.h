#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "world.h"

class Camera {
private:
	// Orientation in world space
	glm::vec3 pos;
	glm::vec3 lookat;
	glm::vec3 up;

	// Film plane parameters
	float focalLength;
	float canvasWidth;
	float canvasHeight;

	// Image parameters
	unsigned imageWidth;
	unsigned imageHeight;

	// World -> Camera transformation matrix
	glm::mat4 matrix;

public:
	// Constructor
	Camera(const glm::vec3 & pos, const glm::vec3 & lookat, const glm::vec3 & up,
		const float focalLength, const float canvasWidth, const float canvasHeight, const unsigned imageWidth, const unsigned imageHeight);

	// Use this camera to render an image of the World
	void render(const World & world, const std::string & filename, const float time) const;
};

#endif