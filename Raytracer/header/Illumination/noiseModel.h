#pragma once
#ifndef NOISE_MODEL_H
#define NOISE_MODEL_H

#include "illuminationModel.h"
#include "../../header/FastNoise/FastNoise.h"

class NoiseModel : public IlluminationModel {
private:
	FastNoise noiseGenerator;

	glm::vec3 primaryColor;
	glm::vec3 secondaryColor;
	glm::vec3 specularColor;

	float ambientConst;
	float diffuseConst;
	float specularConst;
	float specularExp;

public:
	// Constructor
	NoiseModel(const glm::vec3& primaryColor, const glm::vec3& specularColor, const glm::vec3& secondaryColor,
		const float ambientConst, const float diffuseConst, const float SpecularConst, const float specularExp);

	// Override from IlluminationModel
	virtual glm::vec3 illuminate(Intersection intersection, const std::vector<Light>& lights, const bool shadow) const;
	virtual IlluminationModel* interpolate(IlluminationModel* other, const float t) const;
};

#endif