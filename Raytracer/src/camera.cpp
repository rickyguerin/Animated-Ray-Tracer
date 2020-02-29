#include "../header/camera.h"
#include "../header/image.h"
#include "../header/ray.h"
#include "../header/sphere.h"

Camera::Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up, float width, float height, float focalLength) {
	this->pos = pos;
	this->lookat = lookat;
	this->up = up;

	this->width = width;
	this->height = height;
	this->focalLength = focalLength;

	glm::vec3 n = glm::normalize(lookat - pos);
	glm::vec3 u = glm::normalize(glm::cross(up, n));
	glm::vec3 v = glm::normalize(glm::cross(n, u));

	matrix = glm::mat4(
		u.x, u.y, u.z, -glm::dot(u, pos),
		v.x, v.y, v.z, -glm::dot(v, pos),
		n.x, n.y, n.z, -glm::dot(n, pos),
		0.0f, 0.0f, 0.0f, 1.0f
	);

	matrix = glm::mat4(
		u.x, v.x, n.x, 0.0f,
		u.y, v.y, n.y, 0.0f,
		u.z, v.z, n.z, 0.0f,
		-glm::dot(u, pos), -glm::dot(v, pos), -glm::dot(n, pos), 1.0f
	);
}

void Camera::render(World* world, std::string filename, const unsigned imageWidth, const unsigned imageHeight, double time) {

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

			output.setPixel(x, imageHeight - y - 1, world->trace(ray, time));
		}
	}

	output.write(filename);
}

glm::mat4 Camera::getMatrix() {
	return matrix;
}