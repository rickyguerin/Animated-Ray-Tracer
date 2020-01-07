#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>

class Camera {
private:
	// Position
	glm::vec3 pos;
	glm::vec3 lookat;
	glm::vec3 up;

	// Film Plane
	float width{ 16 };
	float height{ 9 };
	float focalLength{ 1 };

public:
	Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up, float width, float height, float focalLength);

	void render(const char* filename, const unsigned imageWidth, const unsigned imageHeight);
};

#endif