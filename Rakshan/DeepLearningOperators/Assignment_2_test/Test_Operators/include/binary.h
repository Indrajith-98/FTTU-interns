#ifndef BINARY_H
#define BINARY_H

#include <vector>
#include <string>
#include <stdexcept>

template<typename T>
std::vector<T> readBinaryFile(const std::string& filename);

std::vector<float> load_binary_file(const std::string& file_path);

#endif // UTILS_H
