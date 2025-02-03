#ifndef MAX_POOL_H
#define MAX_POOL_H

#include <vector>

class MaxPooling {
public:
    MaxPooling(int pool_height, int pool_width);
    std::vector<std::vector<std::vector<double>>> performMaxPooling(
        const std::vector<std::vector<std::vector<double>>>& input_image,
        int image_depth, int image_height, int image_width,
        int stride = 2, int padding = 0
    );

private:
    int pool_height;
    int pool_width;
};

#endif // MAX_POOL_H