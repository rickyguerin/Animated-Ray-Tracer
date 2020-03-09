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
};

#endif