#include <glm/common.hpp>
#include "../../header/Illumination/flatModel.h"

FlatModel::FlatModel(const glm::vec3& color) {
	this->color = color;
}

glm::vec3 FlatModel::illuminate() const {
	return color;
}

IlluminationModel* FlatModel::interpolate(IlluminationModel* other, const float t) const {
	return new FlatModel(glm::mix(this->color, ((FlatModel*)other)->color, t));
}