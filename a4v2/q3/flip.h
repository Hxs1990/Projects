#ifndef FLIP_H
#define FLIP_H

#include "image.h"
#include "imageDecorator.h"

class Flip : public ImageDecorator{
public:
	Flip(Image *i);
	void render(PPM &ppm);
};

#endif