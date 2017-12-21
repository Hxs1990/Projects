//Rotate.h
#ifndef ROTATE_H
#define ROTATE_H

#include "image.h"
#include "imageDecorator.h"

class Rotate : public ImageDecorator{
public:
	Rotate(Image *i);
	void render(PPM &ppm);
};

#endif