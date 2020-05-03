#pragma once
#ifndef FLAT_MODEL_H
#define FLAT_MODEL_H

#include "illuminationModel.h"

class FlatModel : public IlluminationModel {
private:
	// The color
	glm::vec3 color;

public:
	// Constructor
	FlatModel(const glm::vec3& color);

	// Override from IlluminationModel
	virtual glm::vec3 illuminate(Intersection intersection, const std::vector<Light>& lights, const bool shadow) const;
	virtual IlluminationModel* interpolate(IlluminationModel* other, const float t) const;
};

#endif