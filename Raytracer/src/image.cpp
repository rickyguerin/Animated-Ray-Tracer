#include <lodepng.h>
#include "../header/image.h"

Image::Image(const unsigned width, const unsigned height) {
	this->width = width;
	this->height = height;

	this->rgbIlluminance = std::vector<float>(width * height * 3);
	this->logAvgLuminance = 0;
}

void Image::setPixel(const unsigned x, const unsigned y, const glm::vec3& color) {
	for (int i = 0; i < 3; i++) {
		rgbIlluminance[3 * (width * y + x) + i] = color[i];
	}

	logAvgLuminance += log((0.27 * color[0]) + (0.67 * color[1]) + (0.06 * color[2]) + 0.01);
}

void Image::write(const std::string& filename, const float ldmax) {
	std::vector<unsigned char> contents(width * height * 4);

	logAvgLuminance = exp(logAvgLuminance / (width * height));

	float top = 1.219f + pow(ldmax/2.0f, 0.4f);
	float bottom = 1.219f + pow(logAvgLuminance, 0.4f);
	float sf = pow(top / bottom, 2.5f);

	float c;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (int i = 0; i < 3; i++) {
				c = rgbIlluminance[3 * (width * y + x) + i] * sf;
				c = c > ldmax ? 1 : c / ldmax;
				contents[4 * (width * y + x) + i] = c * 255;
			}

			contents[4 * (width * y + x) + 3] = 255;
		}
	}

	lodepng::encode(filename + ".png", contents, width, height);
}