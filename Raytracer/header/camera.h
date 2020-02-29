#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "world.h"

class Camera {
private:
	// Position
	glm::vec3 pos;
	glm::vec3 lookat;
	glm::vec3 up;

	// World -> Camera transformation matrix
	glm::mat4 matrix;

	// Film Plane
	float width{ 16 };
	float height{ 9 };
	float focalLength{ 1 };

public:
	Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up, float width, float height, float focalLength);

	void render(World* world, std::string filename, const unsigned imageWidth, const unsigned imageHeight, double time);

	glm::mat4 getMatrix();
};

#endif