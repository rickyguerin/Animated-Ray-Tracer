#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <glm/vec4.hpp>
#include <vector>

class Image {
private:
	unsigned width;
	unsigned height;
	std::vector<unsigned char> contents;

public:
	Image(unsigned width, unsigned height);

	unsigned getWidth();

	unsigned getHeight();

	void setPixel(long long x, long long y, glm::ivec4 color);

	void write(std::string filename);
};

#endif