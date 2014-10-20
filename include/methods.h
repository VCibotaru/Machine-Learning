#ifndef METHODS_H_
#define METHODS_H_


#include "matrix.h"
#include "EasyBMP.h"


typedef Matrix<int> Image;

BMP* ImgToGrayscale(BMP *img);

BMP* VertSobel(BMP *img);

BMP* HorSobel(BMP *img);

Image* GrayscaleToMatrix(BMP *img);

#endif