#include "methods.h"
#include "EasyBMP.h"
#include <math.h>

#define R 0.299
#define G 0.587
#define B 0.114

Image ImgToGrayscale(BMP *img) {
	Image newImg(img->TellHeight(), img->TellWidth());
	for (uint i = 0 ; i < newImg.n_rows ; ++i) {
		for (uint j = 0 ; j < newImg.n_cols ; ++j) {
			auto pixel = img->GetPixel(j, i);
			int value = pixel.Red * R + pixel.Green * G + pixel.Blue * B;
			newImg(i, j) = value;
		}
	}
	return newImg;
}

std::vector<float> GetHist(const Image &hor, const Image &vert) {
	std::vector<float> result(SEGMENT_COUNT);
	for (uint i = 0 ; i < hor.n_rows ; ++i) {
		for (uint j = 0 ; j < hor.n_cols ; ++j) {
			float angle = std::atan2(vert(i,j), hor(i,j));
			uint section = uint(SEGMENT_COUNT * (angle + M_PI) / (2 * M_PI));
			section = (section == SEGMENT_COUNT) ? SEGMENT_COUNT - 1 : section;
			result[section] += std::sqrt(std::pow(hor(i, j), 2) + std::pow(vert(i, j), 2) );
		}
	}
	float sum = 0;
	for (uint i = 0 ; i < SEGMENT_COUNT ; ++i) {
		sum += result[i] * result[i];
	}
	sum = std::sqrt(sum);
	if (sum) {
		for (uint i = 0 ; i < SEGMENT_COUNT ; ++i) {
			result[i] /= sum;
		}
	}
	return result;
}