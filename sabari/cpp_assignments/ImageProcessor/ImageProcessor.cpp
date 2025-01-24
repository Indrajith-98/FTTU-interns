#include <iostream>
#include <FreeImage.h>
#include <vector>

#include "getopt.h"
#include "imgmanip.h"

void printHelp()
{
	std::cout << "Usage: ImageProcessor -o [ grayscale | blur | sharpen | threshold | edge ] -f <file_path> \n";
	std::cout << "\nNote: Input image must be in BMP format (24-bit, no alpha channel)\n\n";
	std::cout << "Operations:\n";
	std::cout << "  grayscale    Convert RGB image to grayscale\n";
	std::cout << "  blur         Apply Gaussian blur effect\n";
	std::cout << "  sharpen      Enhance image sharpness\n";
	std::cout << "  threshold    Apply binary thresholding\n";
	std::cout << "  edge         Detect edges in the image\n";
	std::cout << "\nOptions:\n";
	std::cout << "  -h         Show this help message\n";
	std::cout << "  -o <op>    Specify the operation to perform\n";
	std::cout << "  -f <file>  Specify the input file path (.bmp)\n";
}

int main(int argc, char *argv[])
{

	const char *operation = nullptr;
	const char *inputFile = nullptr;

	int opt;
	while ((opt = getopt(argc, argv, "ho:f:")) != -1)
	{
		switch (opt)
		{
		case 'h':
			printHelp();
			return 0;
		case 'o':
			operation = optarg;
			break;
		case 'f':
			inputFile = optarg;
			break;
		default:
			printHelp();
			return 1;
		}
	}

	if (!operation || !inputFile)
	{
		std::cout << "[ERROR] Operation and input file must be specified\n";
		printHelp();
		return 1;
	}

	FreeImage_Initialise();

	FIBITMAP *bitmap = FreeImage_Load(FIF_BMP, inputFile, BMP_DEFAULT);

	if (bitmap == nullptr)
	{
		std::cout << "[ERROR] Failed to load the image\n";
		FreeImage_DeInitialise();
		return 1;
	}

	int width = FreeImage_GetWidth(bitmap);
	int height = FreeImage_GetHeight(bitmap);
	int bpp = FreeImage_GetBPP(bitmap);

	if (bpp != 24)
	{
		std::cout << "[ERROR] Only 24-bit images are supported\n";
		FreeImage_DeInitialise();
		return 1;
	}

	BYTE *bits = FreeImage_GetBits(bitmap);

	if (strcmp(operation, "grayscale") == 0)
	{
		if (!convertRGBtoGrayscale(bits, width, height, "sample-grayscale.bmp"))
		{
			std::cout << "[ERROR] Failed to perform the operation\n";
			FreeImage_DeInitialise();
			return 1;
		}
	}
	else if (strcmp(operation, "blur") == 0)
	{
		if (!gaussianBlur(bits, width, height, "sample-blurred.bmp"))
		{
			std::cout << "[ERROR] Failed to perform the operation\n";
			FreeImage_DeInitialise();
			return 1;
		}
	}
	else if (strcmp(operation, "sharpen") == 0)
	{
		if (!sharpening(bits, width, height, "sample-sharpened.bmp"))
		{
			std::cout << "[ERROR] Failed to perform the operation\n";
			FreeImage_DeInitialise();
			return 1;
		}
	}
	else if (strcmp(operation, "threshold") == 0)
	{
		if (!thresholding(bits, width, height, "sample-thresholded.bmp"))
		{
			std::cout << "[ERROR] Failed to perform the operation\n";
			FreeImage_DeInitialise();
			return 1;
		}
	}
	else if (strcmp(operation, "edge") == 0)
	{
		if (!edgeDetection(bits, width, height, "sample-edge-detected.bmp"))
		{
			std::cout << "[ERROR] Failed to perform the operation\n";
			FreeImage_DeInitialise();
			return 1;
		}
	}
	else
	{
		std::cout << "[ERROR] Invalid operation specified\n";
		printHelp();
		FreeImage_DeInitialise();
		return 1;
	}

	std::cout << "Image operation completed successfully\n";

	FreeImage_DeInitialise();

	return 0;
}
