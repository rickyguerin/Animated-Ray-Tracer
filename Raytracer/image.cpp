#include <lodepng.h>

class Image {
private:
	unsigned width;
	unsigned height;
	std::vector<unsigned char> contents;

public:
	Image(unsigned width = 256, unsigned height = 256) {
		this->width = width;
		this->height = height;
		this->contents = std::vector<unsigned char>(long long(width) * long long(height) * 4);
	}

	unsigned getWidth() {
		return width;
	}

	unsigned getHeight() {
		return height;
	}

	void setPixel(long long x, long long y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
		long long lw = long long(width);
		contents[4 * lw * y + 4 * x + 0] = r;
		contents[4 * lw * y + 4 * x + 1] = g;
		contents[4 * lw * y + 4 * x + 2] = b;
		contents[4 * lw * y + 4 * x + 3] = a;
	}

	void write(const char* filename) {
		lodepng::encode(filename, contents, width, height);
	}
};