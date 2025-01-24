#ifndef FILE_COMPARATOR_H
#define FILE_COMPARATOR_H

#include <string>
#include <vector>

// Reads values from a file and returns them as a vector of floats.
std::vector<float> readValuesFromFile(const std::string& file_path);

// Compares two vectors of floats with a specified tolerance (epsilon).
bool compareVectors(const std::vector<float>& vec1, const std::vector<float>& vec2, float epsilon = 0.001);


#endif