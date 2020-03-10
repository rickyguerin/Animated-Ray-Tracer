#pragma once
#ifndef ILLUMINATION_MODEL_H
#define ILLUMINATION_MODEL_H

#include <glm/glm.hpp>

class IlluminationModel {
public:
	// Destructor
	virtual ~IlluminationModel() {};

	// Determine what color to return if a ray collision occurs
	virtual glm::ivec4 illuminate() const = 0;

	// Interpolate between two IlluminationModels of the same type
	virtual IlluminationModel* interpolate(IlluminationModel* other, const float t) const = 0;
};

#endif