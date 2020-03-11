#include "../../header/Illumination/light.h"

void Light::transformToCameraSpace(const glm::mat4& cameraMatrix) {
	position = cameraMatrix * glm::vec4(position, 1.0f);
}