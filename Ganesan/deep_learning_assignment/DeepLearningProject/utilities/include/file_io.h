#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <string>

// Function to read a binary file and return data
std::vector<float> read_binary_file(const std::string& filename);

// Function to write a binary file
void write_binary_file(const std::string& filename, const std::vector<float>& data);

#endif // FILE_IO_H
