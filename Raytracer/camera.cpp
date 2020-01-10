#include <glm/glm.hpp>
#include "camera.h"
#include "image.h"
#include "ray.h"
#include "sphere.h"

Camera::Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up, float width, float height, float focalLength) {
	this->pos = pos;
	this->lookat = lookat;
	this->up = up;

	this->width = width;
	this->height = height;
	this->focalLength = focalLength;
}

void Camera::render(World* world, const char* filename, const unsigned imageWidth, const unsigned imageHeight) {

	Image output(imageWidth, imageHeight);

	const double pixelWidth = width / double(imageWidth);
	const double pixelHeight = height / double(imageHeight);

	const double minX = (pixelWidth - width) / 2;
	const double minY = (pixelHeight - height) / 2;

	Ray ray(pos);
	double px, py;

	for (unsigned y = 0; y < output.getHeight(); y++) {
		for (unsigned x = 0; x < output.getWidth(); x++) {

			px = minX + (pixelWidth * x);
			py = minY + (pixelHeight * y);

			ray.setDirection(glm::normalize(glm::vec3(px, py, focalLength)));

			output.setPixel(x, y, world->trace(ray));
		}
	}

	output.write(filename);
}