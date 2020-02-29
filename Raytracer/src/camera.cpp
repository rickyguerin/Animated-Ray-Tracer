#include "../header/camera.h"
#include "../header/image.h"
#include "../header/sphere.h"

#include <iostream>

Camera::Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up, float angle, float focalLength) {
	this->pos = pos;
	this->lookat = lookat;
	this->up = up;

	this->angle = angle;
	this->focalLength = focalLength;

	glm::vec3 n = glm::normalize(pos - lookat);
	glm::vec3 u = glm::normalize(glm::cross(up, n));
	glm::vec3 v = glm::normalize(glm::cross(n, u));

	matrix = glm::mat4(
		u.x, v.x, n.x, 0.0f,
		u.y, v.y, n.y, 0.0f,
		u.z, v.z, n.z, 0.0f,
		-glm::dot(pos, u), -glm::dot(pos, v), -glm::dot(pos, n), 1.0f
	);
}

glm::mat4 Camera::getMatrix() {
	return matrix;
}

void Camera::render(World* world, std::string filename, const float imageWidth, const float imageHeight, float time) {

	Image output(imageWidth, imageHeight);

	const float canvasHeight = 2 * tan(angle/2) * focalLength;
	const float canvasWidth = canvasHeight * (imageWidth / imageHeight);

	const float pixelWidth = canvasWidth / imageWidth;
	const float pixelHeight = canvasHeight / imageHeight;

	const float minX = (pixelWidth - canvasWidth) / 2;
	const float minY = (pixelHeight - canvasHeight) / 2;

	float px, py;

	for (unsigned y = 0; y < output.getHeight(); y++) {
		for (unsigned x = 0; x < output.getWidth(); x++) {

			px = minX + (pixelWidth * x);
			py = minY + (pixelHeight * y);

			glm::vec3 ray = glm::normalize(glm::vec3(px, py, -focalLength));

			output.setPixel(x, imageHeight - y - 1, world->trace(ray, time));
		}
	}

	output.write(filename);
}