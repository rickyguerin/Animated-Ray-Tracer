#include <algorithm>
#include <glm/common.hpp>
#include "../../header/Illumination/checkerModel.h"

CheckerModel::CheckerModel(const float checkSize, const glm::vec3& primaryColor, const glm::vec3& secondaryColor, const glm::vec3& specularColor,
	const float ambientConst, const float diffuseConst, const float specularConst, const float specularExp,
	const float kReflect, const float kRefract) : IlluminationModel(kReflect, kRefract) {

	this->checkSize = checkSize;
	this->primaryColor = primaryColor;
	this->secondaryColor = secondaryColor;
	this->specularColor = specularColor;

	this->ambientConst = ambientConst;
	this->diffuseConst = diffuseConst;
	this->specularConst = specularConst;
	this->specularExp = specularExp;
}

glm::vec3 CheckerModel::illuminate(Intersection intersection, const std::vector<Light>& lights, const bool shadow) const {

	int u = std::abs((intersection.point.x) / checkSize);
	int v = std::abs((intersection.point.z) / checkSize);

	glm::vec3 checkColor;

	if ((intersection.point.x > 0) == (intersection.point.z > 0)) {
		checkColor = (u % 2 == v % 2) ? primaryColor : secondaryColor;
	}

	else {
		checkColor = (u % 2 == v % 2) ? secondaryColor : primaryColor;
	}

	glm::vec3 ambientPart = checkColor * glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 diffusePart = glm::vec3();
	glm::vec3 specularPart = glm::vec3();

	glm::vec3 src, r;

	if (!shadow) {
		for (int i = 0; i < lights.size(); i++) {
			src = glm::normalize(lights[i].position - intersection.point);
			r = glm::reflect(src, intersection.normal);

			diffusePart += lights[i].color * checkColor * std::max(0.0f, glm::dot(src, intersection.normal));
			specularPart += lights[i].color * specularColor * std::pow(std::max(0.0f, glm::dot(r, intersection.ray)), specularExp);
		}
	}

	return ambientConst * ambientPart + diffuseConst * diffusePart + specularConst * specularPart;
}

IlluminationModel* CheckerModel::interpolate(IlluminationModel* other, const float t) const {
	return new CheckerModel(
		glm::mix(this->checkSize, ((CheckerModel*)other)->checkSize, t),
		glm::mix(this->primaryColor, ((CheckerModel*)other)->primaryColor, t),
		glm::mix(this->secondaryColor, ((CheckerModel*)other)->secondaryColor, t),
		glm::mix(this->specularColor, ((CheckerModel*)other)->specularColor, t),

		glm::mix(this->ambientConst, ((CheckerModel*)other)->ambientConst, t),
		glm::mix(this->diffuseConst, ((CheckerModel*)other)->diffuseConst, t),
		glm::mix(this->specularConst, ((CheckerModel*)other)->specularConst, t),
		glm::mix(this->specularExp, ((CheckerModel*)other)->specularExp, t),
		glm::mix(this->kReflect, other->kReflect, t),
		glm::mix(this->kRefract, other->kRefract, t)
	);
}