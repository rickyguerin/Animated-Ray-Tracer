#include "../../header/Illumination/flatModel.h"

FlatModel::FlatModel(const glm::ivec4 & color) {
	this->color = color;
}

glm::ivec4 FlatModel::illuminate() const {
	return color;
}