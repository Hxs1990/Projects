//imageDecorator.cc
#include "imageDecorator.h"

ImageDecorator::ImageDecorator(Image *i):
	pic{i}{}

ImageDecorator::~ImageDecorator(){
	delete pic;
}

