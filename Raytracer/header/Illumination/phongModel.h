#pragma once
#ifndef PHONG_MODEL_H
#define PHONG_MODEL_H

#include <glm/glm.hpp>

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
		const float ambientConst, const float diffuseConst, const float SpecularConst, const float specularExp);

	// Override from IlluminationModel
	virtual glm::ivec4 illuminate() const;
	virtual IlluminationModel* interpolate(IlluminationModel* other, const float t) const;
};

#endif