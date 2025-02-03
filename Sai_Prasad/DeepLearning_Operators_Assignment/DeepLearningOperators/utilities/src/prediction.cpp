#include "prediction.h"
#include <algorithm>
#include <iostream>

std::string predict_class(const std::vector<float>& output) {
    std::vector<std::string> class_labels = {
        "airplane", "automobile", "bird", "cat", "deer", "dog", "frog", "horse", "ship", "truck"
    };

    auto max_element_it = std::max_element(output.begin(), output.end());
    int predicted_class = std::distance(output.begin(), max_element_it);

    return class_labels[predicted_class];
}
