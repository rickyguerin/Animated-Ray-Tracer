#include <algorithm>
#include <glm/common.hpp>
#include "../../header/Illumination/phongModel.h"

PhongModel::PhongModel(const glm::vec3& diffuseColor, const glm::vec3& specularColor,
	const float ambientConst, const float diffuseConst, const float specularConst, const float specularExp,
	const float kReflect, const float kRefract, const float refIndex) : IlluminationModel(kReflect, kRefract, refIndex) {

	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;

	this->ambientConst = ambientConst;
	this->diffuseConst = diffuseConst;
	this->specularConst = specularConst;
	this->specularExp = specularExp;
}

glm::vec3 PhongModel::illuminate(Intersection intersection, const std::vector<Light>& lights, const bool shadow) const {

	glm::vec3 ambientPart = diffuseColor * glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 diffusePart = glm::vec3();
	glm::vec3 specularPart = glm::vec3();

	glm::vec3 src, r;

	if (!shadow) {
		for (int i = 0; i < lights.size(); i++) {
			src = glm::normalize(lights[i].position - intersection.point);
			r = glm::reflect(src, intersection.normal);

			diffusePart += lights[i].color * diffuseColor * std::max(0.0f, glm::dot(src, intersection.normal));
			specularPart += lights[i].color * specularColor * std::pow(std::max(0.0f, glm::dot(r, intersection.ray)), specularExp);
		}
	}

	return ambientConst * ambientPart + diffuseConst * diffusePart + specularConst * specularPart;
}

IlluminationModel* PhongModel::interpolate(IlluminationModel* other, const float t) const {
	return new PhongModel(
		glm::mix(this->diffuseColor, ((PhongModel*)other)->diffuseColor, t),
		glm::mix(this->specularColor, ((PhongModel*)other)->specularColor, t),

		glm::mix(this->ambientConst, ((PhongModel*)other)->ambientConst, t),
		glm::mix(this->diffuseConst, ((PhongModel*)other)->diffuseConst, t),
		glm::mix(this->specularConst, ((PhongModel*)other)->specularConst, t),
		glm::mix(this->specularExp, ((PhongModel*)other)->specularExp, t),
		glm::mix(this->kReflect, other->kReflect, t),
		glm::mix(this->kRefract, other->kRefract, t),
		glm::mix(this->refIndex, other->refIndex, t)
	);
}