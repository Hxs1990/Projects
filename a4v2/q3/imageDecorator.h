
#ifndef IMAGEDECORATOR_H
#define IMAGEDECORATOR_H

#include "image.h"

class ImageDecorator: public Image {
protected:
	Image *pic;
public:
	ImageDecorator(Image *i);
	virtual ~ImageDecorator();
};

#endif
