#pragma once
#ifndef FLAT_MODEL_H
#define FLAT_MODEL_H

#include <glm/glm.hpp>

#include "illuminationModel.h"

class FlatModel : public IlluminationModel {
private:
	// The color
	glm::ivec4 color;

public:
	// Constructor
	FlatModel(const glm::ivec4 & color);

	// Override from IlluminationModel
	virtual glm::ivec4 illuminate() const;
	virtual IlluminationModel* interpolate(IlluminationModel* other, const float t) const;
};

#endif