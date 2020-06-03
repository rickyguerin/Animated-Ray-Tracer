#pragma once
#ifndef CHECKER_MODEL_H
#define CHECKER_MODEL_H

#include "illuminationModel.h"

class CheckerModel : public IlluminationModel {
private:
	float checkSize;
	glm::vec3 primaryColor;
	glm::vec3 secondaryColor;
	glm::vec3 specularColor;

	float ambientConst;
	float diffuseConst;
	float specularConst;
	float specularExp;

public:
	// Constructor
	CheckerModel(const float checkSize, const glm::vec3& primaryColor, const glm::vec3& secondaryColor,
		const glm::vec3& specularColor, const float ambientConst, const float diffuseConst, const float SpecularConst, const float specularExp, const float kReflect);

	// Override from IlluminationModel
	virtual glm::vec3 illuminate(Intersection intersection, const std::vector<Light>& lights, const bool shadow) const;
	virtual IlluminationModel* interpolate(IlluminationModel* other, const float t) const;
};

#endif