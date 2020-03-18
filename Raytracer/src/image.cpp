#include <lodepng.h>
#include "../../header/image.h"

Image::Image(const unsigned width, const unsigned height) {
	this->width = width;
	this->height = height;
	highest = 0.0f;
	this->filmPlane = std::vector<float>(width * height * 4);
}

void Image::setPixel(const unsigned x, const unsigned y, const glm::vec3& color) {
	for (int i = 0; i < 3; i++) {
		highest = (color[i] > highest) ? color[i] : highest;
		filmPlane[4 * width * y + 4 * x + i] = color[i];
	}
}

void Image::write(const std::string& filename) const {
	std::vector<unsigned char> contents(width * height * 4);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			for (int i = 0; i < 3; i++) {
				unsigned char finalColor = filmPlane[4 * width * y + 4 * x + i] / highest * 255;
				contents[4 * width * y + 4 * x + i] = finalColor;
			}

			contents[4 * width * y + 4 * x + 3] = 255;
		}
	}

	lodepng::encode(filename, contents, width, height);
}