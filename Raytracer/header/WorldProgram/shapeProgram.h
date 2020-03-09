#pragma once
#ifndef SHAPEPROG_H
#define SHAPEPROG_H

#include "../Shape/shape.h"

class ShapeProgram {
public:
	// Destructor
	virtual ~ShapeProgram() {}

	// Interpolate between frames to get the Shape at the given time
	virtual Shape * getShape(const float time) const = 0;
};

#endif