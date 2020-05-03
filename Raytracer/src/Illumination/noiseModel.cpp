#include <algorithm>
#include <glm/common.hpp>
#include "../../header/Illumination/noiseModel.h"

NoiseModel::NoiseModel(const glm::vec3& diffuseColor, const glm::vec3& specularColor,
	const float ambientConst, const float diffuseConst, const float specularConst, const float specularExp) {

	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;

	this->ambientConst = ambientConst;
	this->diffuseConst = diffuseConst;
	this->specularConst = specularConst;
	this->specularExp = specularExp;
}

glm::vec3 NoiseModel::illuminate(Intersection intersection, const std::vector<Light>& lights, const bool shadow) const {

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

IlluminationModel* NoiseModel::interpolate(IlluminationModel* other, const float t) const {
	return new NoiseModel(
		glm::mix(this->diffuseColor, ((NoiseModel*)other)->diffuseColor, t),
		glm::mix(this->specularColor, ((NoiseModel*)other)->specularColor, t),

		glm::mix(this->ambientConst, ((NoiseModel*)other)->ambientConst, t),
		glm::mix(this->diffuseConst, ((NoiseModel*)other)->diffuseConst, t),
		glm::mix(this->specularConst, ((NoiseModel*)other)->specularConst, t),
		glm::mix(this->specularExp, ((NoiseModel*)other)->specularExp, t)
	);
}