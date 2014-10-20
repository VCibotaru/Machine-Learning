#include "methods.h"
#include "EasyBMP.h"

#define R 0.299
#define G 0.587
#define B 0.114

BMP* ImgToGrayscale(BMP *img) {
	BMP *newImg = new BMP();
	newImg->SetSize(img->TellWidth(), img->TellHeight());
	for (int i = 0 ; i < img->TellWidth() ; ++i) {
		for (int j = 0 ; j < img->TellHeight() ; ++j) {
			auto pixel = img->GetPixel(i, j);
			float value = pixel.Red * R + pixel.Green * G + pixel.Blue * B;
			RGBApixel newPixel;
			newPixel.Red = value;
			newPixel.Green = value;
			newPixel.Blue = value;
			newImg->SetPixel(i, j, newPixel);
		}
	}
	return newImg;
}

Image* VertSobel(Image *img) {
	Image *newImg = new Image(img->n_rows, img->n_cols);
	for (uint i = 0 ; i < img->n_rows ; ++i) {
		for (uint j = 1 ; j < img->n_cols - 1 ; ++j) {
			int first = (*img)(i, j - 1);
			int third = (*img)(i, j + 1);
			(*newImg)(i, j) = first - third;
		}
	}
	return newImg;
}

Image* HorSobel(Image *img) {
	Image *newImg = new Image(img->n_rows, img->n_cols);
	for (uint i = 1 ; i < img->n_rows - 1 ; ++i) {
		for (uint j = 0 ; j < img->n_cols ; ++j) {
			int first = (*img)(i - 1, j);
			int third = (*img)(i + 1, j);
			(*newImg)(i, j) = third - first;
		}
	}
	return newImg;
}

Image* GrayscaleToMatrix(BMP *img) {
	Image *newImg = new Image(img->TellHeight(), img->TellWidth());
	for (int i = 0 ; i < img->TellWidth() ; ++i) {
		for (int j = 0 ; j < img->TellHeight() ; ++j) {
			auto pixel = img->GetPixel(i, j);
			int value = pixel.Red * R + pixel.Green * G + pixel.Blue * B;
			(*newImg)(j, i) = value;
		}
	}
	return newImg;
}