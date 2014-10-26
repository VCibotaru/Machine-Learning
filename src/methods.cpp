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
			float angle = atan2(vert(i,j), hor(i,j));
			uint section = uint(SEGMENT_COUNT * (angle + M_PI) / (2 * M_PI));
			section = (section == SEGMENT_COUNT) ? SEGMENT_COUNT - 1 : section;
			result[section] += sqrt(pow(hor(i, j), 2) + pow(vert(i, j), 2) );
		}
	}
	float sum = 0;
	for (uint i = 0 ; i < SEGMENT_COUNT ; ++i) {
		sum += result[i] * result[i];
	}
	sum = sqrt(sum);
	if (sum) {
		for (uint i = 0 ; i < SEGMENT_COUNT ; ++i) {
			result[i] /= sum;
		}
	}
	return result;
}

float sech(float x) {
	return 2.0 / (exp(x) + exp(-x));
}
std::vector<float> ApplyHIKernel(const std::vector<float> &preHI) {
	std::vector <float> postHI;
	for (float x : preHI) {
		for (int j = -N ; j <= N ; ++j) {
			if (x) {
				float im = - sqrt(x * sech(M_PI * j * L)) * sin(j * L * log(x));
				float re = sqrt(x * sech(M_PI * j * L)) * cos(j * L * log(x));
				postHI.push_back(im);
				postHI.push_back(re);
			}
			else {
				postHI.push_back(0.0);
				postHI.push_back(0.0);
			}
		}
	}
	return postHI;
}