#ifndef COMPARE_H
#define COMPARE_H

#include <vector>
#include <iostream>
#include <cmath>

// ✅ Function to compare outputs within a small tolerance
bool compare_outputs(const std::vector<float>& output, const std::vector<float>& reference, float tolerance = 1e-5);

#endif // COMPARE_H
