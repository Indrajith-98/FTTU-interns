#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <string>

bool read_image_file(const std::string& imagePath, std::vector<float>& outputVector);

void write_output_to_file(const std::vector<float>& outputVector, const std::string& layer_name);

std::vector<float> read_binary_file(const std::string& filename);

#endif  
