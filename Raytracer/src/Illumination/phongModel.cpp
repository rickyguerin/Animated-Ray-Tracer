#include <glm/common.hpp>
#include "../../header/Illumination/phongModel.h"

PhongModel::PhongModel(const glm::vec3& diffuseColor, const glm::vec3& specularColor,
	const float ambientConst, const float diffuseConst, const float specularConst, const float specularExp) {

	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;

	this->ambientConst = ambientConst;
	this->diffuseConst = diffuseConst;
	this->specularConst = specularConst;
	this->specularExp = specularExp;
}

glm::vec3 PhongModel::illuminate(Intersection intersection, const std::vector<Light>& lights) const {
	return diffuseColor;
}

IlluminationModel* PhongModel::interpolate(IlluminationModel* other, const float t) const {
	return new PhongModel(
		glm::mix(this->diffuseColor, ((PhongModel*)other)->diffuseColor, t),
		glm::mix(this->specularColor, ((PhongModel*)other)->specularColor, t),

		glm::mix(this->ambientConst, ((PhongModel*)other)->ambientConst, t),
		glm::mix(this->diffuseConst, ((PhongModel*)other)->diffuseConst, t),
		glm::mix(this->specularConst, ((PhongModel*)other)->specularConst, t),
		glm::mix(this->specularExp, ((PhongModel*)other)->specularExp, t)
	);
}