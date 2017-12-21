#ifndef SEPIA_H
#define SEPIA_H

#include "image.h"
#include "imageDecorator.h"

class Sepia : public ImageDecorator{
public:
	Sepia(Image *i);
	void render(PPM &ppm);
};
#endif