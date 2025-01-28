#pragma once
#include <vector>

namespace Utility {
	std::vector<std::vector<float>> createGaussianKernel(int size, float sigma);
}