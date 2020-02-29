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

	// World -> Camera transformation matrix
	glm::mat4 matrix;

	// Field of view parameters
	float angle;
	float focalLength;

public:
	// Constructor
	Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up, float angle, float focalLength);

	// Access this Camera's transformation matrix
	glm::mat4 getMatrix();

	// Use this camera to render an image of the World
	void render(World* world, std::string filename, const float imageWidth, const float imageHeight, float time);
};

#endif