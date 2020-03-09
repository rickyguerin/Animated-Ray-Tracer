#include "../../header/Illumination/flatModel.h"

FlatModel::FlatModel(const glm::ivec4 & color) {
	this->color = color;
}

glm::ivec4 FlatModel::illuminate() const {
	return color;
}

IlluminationModel* FlatModel::interpolate(IlluminationModel* other, const float t) const {
	return new FlatModel(glm::mix(this->color, ((FlatModel*)other)->color, t));
}