#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <glm/vec4.hpp>
#include <vector>

class Image {
private:
	// Image dimensions
	unsigned width;
	unsigned height;

	// Image pixel colors
	std::vector<unsigned char> contents;

public:
	// Constructor
	Image(unsigned width, unsigned height);

	// Accessors
	unsigned getWidth();
	unsigned getHeight();

	// Set the color of one pixel in the Image
	void setPixel(long long x, long long y, glm::ivec4 color);

	// Write the contents of this Image to a file
	void write(std::string filename);
};

#endif