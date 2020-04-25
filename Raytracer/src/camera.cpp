#include <glm/glm.hpp>
#include "../header/camera.h"
#include "../header/image.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& lookat, const glm::vec3& up, const float focalLength, const float canvasWidth, const float canvasHeight, const float ldmax, const unsigned sampleLevel) {
	this->eye = eye;
	this->lookat = lookat;
	this->up = up;

	this->focalLength = focalLength;
	this->canvasWidth = canvasWidth;
	this->canvasHeight = canvasHeight;
	this->ldmax = ldmax;
	this->sampleLevel = sampleLevel;

	// Build World -> Camera matrix
	glm::vec3 n = glm::normalize(eye - lookat);
	glm::vec3 u = glm::normalize(glm::cross(up, n));
	glm::vec3 v = glm::normalize(glm::cross(n, u));

	matrix = glm::mat4(
		u.x, v.x, n.x, 0.0f,
		u.y, v.y, n.y, 0.0f,
		u.z, v.z, n.z, 0.0f,
		-glm::dot(eye, u), -glm::dot(eye, v), -glm::dot(eye, n), 1.0f
	);
}

// Return the average color of all colors in a vector
glm::vec3 averageColor(const std::vector<glm::vec3>& colors) {
	glm::vec3 avg = glm::vec3();

	for (int i = 0; i < colors.size(); i++) {
		avg += colors[i];
	}

	return avg.operator/=(colors.size());
}

void Camera::render(World& world, const std::string& filename, const unsigned imageWidth, const unsigned imageHeight, const float time) const {
	// Get World in Camera space for this image
	world.loadCurrent(matrix, time);

	// Create output Image
	Image output(imageWidth, imageHeight);

	// World space dimensions of one pixel of the Image
	const float pixelWidth = canvasWidth / imageWidth;
	const float pixelHeight = canvasHeight / imageHeight;

	const float qpw = pixelWidth / 4;
	const float qph = pixelHeight / 4;

	// Minimum X/Y value of a pixel in the Image
	const float minX = (pixelWidth - canvasWidth) / 2;
	const float minY = (pixelHeight - canvasHeight) / 2;

	// Fire a ray through each pixel to render the Image
	float px, py;

	// Modifiers for supersampling
	float ssx[4] = { -qpw, qpw, -qpw, qpw };
	float ssy[4] = { -qph, -qph, qph, qph };

	// Color vector for supersampling
	std::vector<glm::vec3> colors;

	for (unsigned y = 0; y < imageHeight; y++) {
		for (unsigned x = 0; x < imageWidth; x++) {
			for (int i = 0; i < 4; i++) {
				px = minX + (pixelWidth * x) + ssx[i];
				py = minY + (pixelHeight * y) + ssy[i];

				glm::vec3 ray = glm::normalize(glm::vec3(px, py, -focalLength));

				colors.push_back(world.trace(ray, time));
			}

			output.setPixel(x, imageHeight - y - 1, averageColor(colors) * ldmax);
			colors.clear();
		}
	}

	// Save Image to file
	output.write(filename, ldmax);

	// Delete Shapes
	world.deleteCurrent();
}