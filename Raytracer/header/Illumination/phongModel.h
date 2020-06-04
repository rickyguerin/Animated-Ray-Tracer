#pragma once
#ifndef PHONG_MODEL_H
#define PHONG_MODEL_H

#include "illuminationModel.h"

class PhongModel : public IlluminationModel {
private:
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

	float ambientConst;
	float diffuseConst;
	float specularConst;
	float specularExp;

public:
	// Constructor
	PhongModel(const glm::vec3& diffuseColor, const glm::vec3& specularColor,
		const float ambientConst, const float diffuseConst, const float SpecularConst, const float specularExp,
		const float kReflect, const float kRefract);

	// Override from IlluminationModel
	virtual glm::vec3 illuminate(Intersection intersection, const std::vector<Light>& lights, const bool shadow) const;
	virtual IlluminationModel* interpolate(IlluminationModel* other, const float t) const;
};

#endif