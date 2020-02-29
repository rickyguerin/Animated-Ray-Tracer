#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/glm.hpp>
#include "ray.h"

struct SphereFrame {
	double timestamp;
	glm::vec3 position;
	glm::ivec4 color;
	double radius;
};

class Sphere {
private:
	std::vector<SphereFrame> frames;

public:
	void addFrame(SphereFrame frame);

	unsigned getCurrentFrame(double time);

	glm::vec3 getPos(unsigned frame, double time);

	glm::ivec4 getColor(unsigned frame, double time);

	double getRadius(unsigned frame, double time);

	bool collision(Ray ray, double time);

	void transformToCameraSpace(glm::mat4 cameraMatrix);
};

#endif