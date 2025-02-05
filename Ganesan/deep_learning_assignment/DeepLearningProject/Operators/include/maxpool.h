#ifndef MAXPOOL_H
#define MAXPOOL_H

#include <vector>

void maxpool(const std::vector<float>& input_data, std::vector<float>& output_data, 
             int input_height, int input_width, int kernel_size, int stride);

#endif // MAXPOOL_H
