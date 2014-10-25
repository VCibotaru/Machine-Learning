#ifndef METHODS_H_
#define METHODS_H_


#include "matrix.h"
#include "EasyBMP.h"



const uint CELL_SIZE  = 16;
const uint SEGMENT_COUNT = 10;

typedef Matrix<float> Image;


class VertSobel 
{
public:
    const int vert_radius;
    const int hor_radius;
    VertSobel() : vert_radius(1), hor_radius(0) {}
    float operator () (const Image &mat) const
    {
        return -mat(0, 0) + mat(2, 0);
    }
};

class HorSobel
{
public:
    const int vert_radius;
    const int hor_radius;
    HorSobel() : vert_radius(0), hor_radius(1) {}
    float operator () (const Image &mat) const
    {
        return -mat(0, 0) + mat(0, 2); 
    }
};

Image ImgToGrayscale(BMP *img);
Image Magnitude(const Image &hor, const Image &vert);
Image Direction(const Image &hor, const Image &vert);
std::vector<float> GetHist(const Image &magn, const Image &dir);
#endif