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

	// Film Plane parameters
	float width{ 16 };
	float height{ 9 };
	float focalLength{ 1 };

public:
	// Constructor
	Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up, float width, float height, float focalLength);

	// Access this Camera's transformation matrix
	glm::mat4 getMatrix();

	// Use this camera to render an image of the World
	void render(World* world, std::string filename, const unsigned imageWidth, const unsigned imageHeight, double time);
};

#endif