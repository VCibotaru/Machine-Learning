#include "methods.h"
#include "EasyBMP.h"
#include <math.h>

#define R 0.299
#define G 0.587
#define B 0.114

Image ImgToGrayscale(BMP *img) {
	Image newImg(img->TellWidth(), img->TellHeight());
	for (int i = 0 ; i < img->TellWidth() ; ++i) {
		for (int j = 0 ; j < img->TellHeight() ; ++j) {
			auto pixel = img->GetPixel(i, j);
			float value = pixel.Red * R + pixel.Green * G + pixel.Blue * B;
			newImg(i, j) = value;
		}
	}
	return newImg;
}

Image Magnitude(const Image &hor, const Image &vert) {
	Image newImg(hor.n_rows, hor.n_cols);
	for (uint i = 0 ; i < hor.n_rows ; ++i) {
		for (uint j = 0 ; j < hor.n_cols ; ++j) {
			float a = std::pow(hor(i, j), 2);
			float b = std::pow(vert(i, j), 2);
			newImg(i, j) = std::sqrt(a + b);
		}
	}
	return newImg;

}
Image Direction(const Image &hor, const Image &vert) {
	Image newImg(hor.n_rows, hor.n_cols);
	for (uint i = 0 ; i < hor.n_rows ; ++i) {
		for (uint j = 0 ; j < hor.n_cols ; ++j) {
			float x = hor(i, j);
			float y = vert(i, j);
			newImg(i, j) = std::atan2(y, x);
		}
	}
	return newImg;
}

std::vector<float> GetHist(const Image &magn, const Image &dir) {
	std::vector<float> result(SEGMENT_COUNT);
	for (uint i = 0 ; i < dir.n_rows ; ++i) {
		for (uint j = 0 ; j < dir.n_cols ; ++j) {
			float angle = dir(i, j);
			uint section = int(SEGMENT_COUNT * (angle + M_PI) / (2 * M_PI));
			section = (section == SEGMENT_COUNT) ? SEGMENT_COUNT - 1 : section;
			result[section] += magn(i, j);
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