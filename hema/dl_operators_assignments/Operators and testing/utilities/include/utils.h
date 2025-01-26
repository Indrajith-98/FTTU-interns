#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <fstream>
#include <chrono>
#include <stdexcept>
#include <string>
#include <iostream>

std::vector<float> read_weights_from_file(const std::string& file_path);

void print_3d_vector(const std::vector<std::vector<std::vector<float>>> &vec, const std::string &file_path);

void print_1d_vector(const std::vector<float> &vec, const std::string &file_path);

std::vector<std::vector<std::vector<float>>> read_image_from_file(const std::string& filename, int width, int height);

template <typename T>
void print_dimensions(const std::string& layer_name, const T& tensor);

template <typename Func>
auto measure_time(const std::string &layer_name, Func func) -> decltype(func()) {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = func(); // Execute the function
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << layer_name << " Execution Time: " << elapsed.count() << " seconds\n";
    return result;
}

#endif
