#ifndef UTILS_H
#define UTILS_H
#include <iomanip>
#include <vector>
#include <string>
#include <array>
#include <stdexcept>

template<typename T>
std::vector<T> readBinaryFile(const std::string& filename);

std::vector<float> load_binary_file(const std::string& file_path);

// Function declaration with default argument
void store_data_to_file(const std::vector<float>& output,
                        const std::array<int, 4>& output_shape,
                        const std::string& layer_name,
                        const std::string& folder_path);
#endif // UTILS_H
 