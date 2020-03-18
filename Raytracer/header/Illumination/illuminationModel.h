#pragma once
#ifndef ILLUMINATION_MODEL_H
#define ILLUMINATION_MODEL_H

#include <vector>
#include <glm/vec3.hpp>
#include "../Math/intersection.h"
#include "../Illumination/light.h"

class IlluminationModel {
public:
	// Destructor
	virtual ~IlluminationModel() {};

	// Determine what color to return if a ray collision occurs
	virtual glm::vec3 illuminate(Intersection intersection, const std::vector<Light>& lights) const = 0;

	// Interpolate between two IlluminationModels of the same type
	virtual IlluminationModel* interpolate(IlluminationModel* other, const float t) const = 0;
};

#endif