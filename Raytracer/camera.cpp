#include <glm/vec3.hpp>
#include "image.cpp"
#include "ray.cpp"

class Camera {
private:
	// Position
	glm::vec3 pos;
	glm::vec3 lookat;
	glm::vec3 up;

	// Film Plane
	unsigned width{ 256 };
	unsigned height{ 256 };
	float focalLength{ 1 };

public:
	Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up, unsigned width, unsigned height, float focalLength) {
		this->pos = pos;
		this->lookat = lookat;
		this->up = up;

		this->width = width;
		this->height = height;
		this->focalLength = focalLength;
	}

	void render(const char* filename) {
		Image output(width, height);

		Ray r(pos);

		for (unsigned y = 0; y < output.getHeight(); y++) {
			for (unsigned x = 0; x < output.getWidth(); x++) {
				output.setPixel(x, y, 255 * !(x & y), x | y, x | y, 255);
			}
		}

		output.write(filename);
	}
};