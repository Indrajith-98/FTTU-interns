#pragma once

#include <FreeImage.h>

bool convertRGBtoGrayscale(const BYTE* imageData, int width, int height, const char* fileName);
bool gaussianBlur(const BYTE* imageData, int width, int height, const char* fileName, int kernelSize = 7, float sigma = 5.0f);
bool sharpening(const BYTE* imageData, int width, int height, const char* fileName);
bool thresholding(const BYTE* imageData, int width, int height, const char* fileName, int threshold = 128);
bool edgeDetection(const BYTE* imageData, int width, int height, const char* fileName);