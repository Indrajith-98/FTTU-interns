#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

std::vector<float> readBinaryFile(const std::string& filePath);
void writeBinaryFile(const std::string& filePath, const std::vector<float>& data);

#endif // UTILS_H
