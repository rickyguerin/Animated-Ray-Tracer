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

void Camera::render(const char* filename, const unsigned imageWidth, const unsigned imageHeight) {

	Image output(imageWidth, imageHeight);

	const double pixelWidth = width / double(imageWidth);
	const double pixelHeight = height / double(imageHeight);

	const double minX = (pixelWidth - width) / 2;
	const double minY = (pixelHeight - height) / 2;

	Ray ray(pos);
	double px, py;

	glm::vec3 sphereLoc(0, 0, 10);
	Sphere sphere(sphereLoc, 2);

	for (unsigned y = 0; y < output.getHeight(); y++) {
		for (unsigned x = 0; x < output.getWidth(); x++) {

			px = minX + (pixelWidth * x);
			py = minY + (pixelHeight * y);

			ray.setDirection(glm::normalize(glm::vec3(px, py, focalLength)));

			if (sphere.collision(ray)) {
				output.setPixel(x, y, 255, 0, 0, 255);
			}
			else {
				if (double(rand()) / (double(RAND_MAX) + 1.0) < 0.001) {
					output.setPixel(x, y, 255, 255, 255, 255);
				}
				else {
					output.setPixel(x, y, 0, 0, 0, 255);
				}
			}
		}
	}

	output.write(filename);
}