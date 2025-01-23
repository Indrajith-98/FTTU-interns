#include <iostream>
#include <vector>

#include "utility.h"

#include "imgmanip.h"

bool convertRGBtoGrayscale(const BYTE* imageData, int width, int height, const char* fileName) {
	FIBITMAP* bitmap = FreeImage_Allocate(width, height, 8);
	if (!bitmap) {
		std::cout << "[ERROR] Failed to allocate the image\n";
		return false;
	}

	BYTE* bits = FreeImage_GetBits(bitmap);
	if (!bits) {
		std::cout << "[ERROR] Failed to get the bits of the image\n";
		FreeImage_Unload(bitmap);
		return false;
	}

	for (int i = 0; i < width * height; i++) {
		BYTE r = imageData[i * 3 + 0];
		BYTE g = imageData[i * 3 + 1];
		BYTE b = imageData[i * 3 + 2];
		bits[i] = (BYTE)(0.299 * r + 0.587 * g + 0.114 * b);
	}

	if (!FreeImage_Save(FIF_BMP, bitmap, fileName, BMP_DEFAULT)) {
		std::cout << "[ERROR] Failed to save the image\n";
		FreeImage_Unload(bitmap);
		return false;
	}

	FreeImage_Unload(bitmap);
	return true;
}

bool gaussianBlur(const BYTE* imageData, int width, int height, const char* fileName, int kernelSize, float sigma) {
	
    std::vector<std::vector<float>> kernel = Utility::createGaussianKernel(kernelSize, sigma);
	if (kernel.empty()) return false;

    const int inputPitch = width * 3;

	const int newWidth = width - (kernelSize - 1);
	const int newHeight = height - (kernelSize - 1);

    FIBITMAP* bitmap = FreeImage_Allocate(
		newWidth,
		newHeight,
        24
    );
    if (!bitmap) {
        std::cout << "[ERROR] Failed to allocate the image\n";
        return false;
    }

    BYTE* bits = FreeImage_GetBits(bitmap);
    const int outputPitch = FreeImage_GetPitch(bitmap); // Get the actual output pitch

    for (int h = 0; h < newHeight; h++) {
        BYTE* outputScanline = bits + h * outputPitch;
        for (int w = 0; w < newWidth; w++) {
            float r = 0.0f, g = 0.0f, b = 0.0f;


            for (int i = 0; i < kernelSize; i++) {
                const BYTE* inputScanline = imageData + (h + i) * inputPitch;
                for (int j = 0; j < kernelSize; j++) {
                    const int pixelIndex = (w + j) * 3;
                    r += inputScanline[pixelIndex + 0] * kernel[i][j];
                    g += inputScanline[pixelIndex + 1] * kernel[i][j];
                    b += inputScanline[pixelIndex + 2] * kernel[i][j];
                }
            }
            outputScanline[w * 3 + 0] = static_cast<BYTE>(r);
            outputScanline[w * 3 + 1] = static_cast<BYTE>(g);
            outputScanline[w * 3 + 2] = static_cast<BYTE>(b);
        }
    }

    if (!FreeImage_Save(FIF_BMP, bitmap, fileName, BMP_DEFAULT)) {
        std::cout << "[ERROR] Failed to save the image\n";
        FreeImage_Unload(bitmap);
        return false;
    }

    FreeImage_Unload(bitmap);
    return true;
}

bool sharpening(const BYTE* imageData, int width, int height, const char* fileName)
{
    std::vector<std::vector<float>> kernel = {
		{ 0, -1, 0 },
		{ -1, 5, -1 },
		{ 0, -1, 0 }
	};

    const int inputPitch = width * 3;

    const int newWidth = width - 2;
    const int newHeight = height - 2;

    FIBITMAP* bitmap = FreeImage_Allocate(
        newWidth,
        newHeight,
        24
    );
    if (!bitmap) {
        std::cout << "[ERROR] Failed to allocate the image\n";
        return false;
    }

    BYTE* bits = FreeImage_GetBits(bitmap);
    const int outputPitch = FreeImage_GetPitch(bitmap); // Get the actual output pitch

    for (int h = 0; h < newHeight; h++) {
        BYTE* outputScanline = bits + h * outputPitch;
        for (int w = 0; w < newWidth; w++) {
            float r = 0.0f, g = 0.0f, b = 0.0f;


            for (int i = 0; i < 3; i++) {
                const BYTE* inputScanline = imageData + (h + i) * inputPitch;
                for (int j = 0; j < 3; j++) {
                    const int pixelIndex = (w + j) * 3;
                    r += inputScanline[pixelIndex + 0] * kernel[i][j];
                    g += inputScanline[pixelIndex + 1] * kernel[i][j];
                    b += inputScanline[pixelIndex + 2] * kernel[i][j];
                }
            }

			// clamp the values to [0, 255]
			r = std::min(std::max(r, 0.0f), 255.0f);
			g = std::min(std::max(g, 0.0f), 255.0f);
			b = std::min(std::max(b, 0.0f), 255.0f);

            outputScanline[w * 3 + 0] = static_cast<BYTE>(r);
            outputScanline[w * 3 + 1] = static_cast<BYTE>(g);
            outputScanline[w * 3 + 2] = static_cast<BYTE>(b);
        }
    }

    if (!FreeImage_Save(FIF_BMP, bitmap, fileName, BMP_DEFAULT)) {
        std::cout << "[ERROR] Failed to save the image\n";
        FreeImage_Unload(bitmap);
        return false;
    }

    FreeImage_Unload(bitmap);
    return true;
}

bool thresholding(const BYTE* imageData, int width, int height, const char* fileName, int threshold)
{
    FIBITMAP* bitmap = FreeImage_Allocate(width, height, 8);
    if (!bitmap) {
        std::cout << "[ERROR] Failed to allocate the image\n";
        return false;
    }

    BYTE* bits = FreeImage_GetBits(bitmap);
    if (!bits) {
        std::cout << "[ERROR] Failed to get the bits of the image\n";
        FreeImage_Unload(bitmap);
        return false;
    }

    for (int i = 0; i < width * height; i++) {
        BYTE r = imageData[i * 3 + 0];
        BYTE g = imageData[i * 3 + 1];
        BYTE b = imageData[i * 3 + 2];
        
		if ((r + g + b) / 3 > threshold)
			bits[i] = 255;
		else
			bits[i] = 0;

    }

    if (!FreeImage_Save(FIF_BMP, bitmap, fileName, BMP_DEFAULT)) {
        std::cout << "[ERROR] Failed to save the image\n";
        FreeImage_Unload(bitmap);
        return false;
    }

    FreeImage_Unload(bitmap);
    return true;
}

bool edgeDetection(const BYTE* imageData, int width, int height, const char* fileName)
{
    std::vector<std::vector<float>> kernel = {
        { 0, -1, 0 },
        { -1, 4, -1 },
        { 0, -1, 0 }
    };

    const int inputPitch = width * 3;

    const int newWidth = width - 2;
    const int newHeight = height - 2;

    FIBITMAP* bitmap = FreeImage_Allocate(
        newWidth,
        newHeight,
        24
    );
    if (!bitmap) {
        std::cout << "[ERROR] Failed to allocate the image\n";
        return false;
    }

    BYTE* bits = FreeImage_GetBits(bitmap);
    const int outputPitch = FreeImage_GetPitch(bitmap); // Get the actual output pitch

    for (int h = 0; h < newHeight; h++) {
        BYTE* outputScanline = bits + h * outputPitch;
        for (int w = 0; w < newWidth; w++) {
            float r = 0.0f, g = 0.0f, b = 0.0f;


            for (int i = 0; i < 3; i++) {
                const BYTE* inputScanline = imageData + (h + i) * inputPitch;
                for (int j = 0; j < 3; j++) {
                    const int pixelIndex = (w + j) * 3;
                    r += inputScanline[pixelIndex + 0] * kernel[i][j];
                    g += inputScanline[pixelIndex + 1] * kernel[i][j];
                    b += inputScanline[pixelIndex + 2] * kernel[i][j];
                }
            }

            // clamp the values to [0, 255]
            r = std::min(std::max(r, 0.0f), 255.0f);
            g = std::min(std::max(g, 0.0f), 255.0f);
            b = std::min(std::max(b, 0.0f), 255.0f);

            outputScanline[w * 3 + 0] = static_cast<BYTE>(r);
            outputScanline[w * 3 + 1] = static_cast<BYTE>(g);
            outputScanline[w * 3 + 2] = static_cast<BYTE>(b);
        }
    }

    if (!FreeImage_Save(FIF_BMP, bitmap, fileName, BMP_DEFAULT)) {
        std::cout << "[ERROR] Failed to save the image\n";
        FreeImage_Unload(bitmap);
        return false;
    }

    FreeImage_Unload(bitmap);
    return true;
}
