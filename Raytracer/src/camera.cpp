#include "../header/camera.h"
#include "../header/image.h"
#include "../header/sphere.h"

#include <iostream>

Camera::Camera(const glm::vec3 & pos, const glm::vec3 & lookat, const glm::vec3 & up, const float angle, const float focalLength) {
	this->pos = pos;
	this->lookat = lookat;
	this->up = up;

	this->angle = angle;
	this->focalLength = focalLength;

	// Build World -> Camera matrix
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

void Camera::render(const World & world, const std::string & filename, const float imageWidth, const float imageHeight, const float time) const {

	// Create output Image
	Image output(imageWidth, imageHeight);

	// World space dimensions of canvas
	const float canvasHeight = 2 * tan(angle/2) * focalLength;
	const float canvasWidth = canvasHeight * (imageWidth / imageHeight);

	// World space dimensions of one pixel of the Image
	const float pixelWidth = canvasWidth / imageWidth;
	const float pixelHeight = canvasHeight / imageHeight;

	// Minimum X/Y value of a pixel in the Image
	const float minX = (pixelWidth - canvasWidth) / 2;
	const float minY = (pixelHeight - canvasHeight) / 2;

	// Fire a ray through each pixel to render the Image
	float px, py;

	for (unsigned y = 0; y < imageHeight; y++) {
		for (unsigned x = 0; x < imageWidth; x++) {

			px = minX + (pixelWidth * x);
			py = minY + (pixelHeight * y);

			glm::vec3 ray = glm::normalize(glm::vec3(px, py, -focalLength));

			output.setPixel(x, imageHeight - y - 1, world.trace(matrix, ray, time));
		}
	}

	// Save Image to file
	output.write(filename);
}