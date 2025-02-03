#include "cnn_functions.h"
#include "../utilities/include/image_reader.h"
#include "../utilities/include/json_handler.h"
#include "../utilities/include/tensor_ops.h"
#include <nlohmann/json.hpp>
#include <fstream>

template <typename T>
void saveToFile(const std::string &filename, const T &data) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << nlohmann::json(data).dump(4);
        file.close();
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

int main() {
    ImageReader img_reader = ImageReader("F:/MULTICOREWARE_FTU_INTERN/DEEP_LEARNING_OPERATORS/mnist_images/mnist_image_5.png");
    std::vector<std::vector<std::vector<double>>> img_vector = img_reader.readImage();
    saveToFile("F:/MULTICOREWARE_FTU_INTERN/DEEP_LEARNING_OPERATORS/data/input/inputimage_vector.json", img_vector);

    JsonHandler json_handler = JsonHandler("F:/MULTICOREWARE_FTU_INTERN/DEEP_LEARNING_OPERATORS/configs/configs.json");
    bool file_opened = json_handler.openJsonFile();
    nlohmann::json jsonData = json_handler.getJsonData();
    TensorOps tensor_ops = TensorOps(jsonData);

    std::vector<std::vector<std::vector<double>>> max_pooled_feature_maps_1 = performConvolutionAndPooling("conv2d", "max_pooling2d", img_vector, tensor_ops);
    saveToFile("F:/MULTICOREWARE_FTU_INTERN/DEEP_LEARNING_OPERATORS/data/output/max_pooled_feature_maps_1.json", max_pooled_feature_maps_1);

    std::vector<std::vector<std::vector<double>>> max_pooled_feature_maps_2 = performConvolutionAndPooling("conv2d_1", "max_pooling2d_1", max_pooled_feature_maps_1, tensor_ops);
    saveToFile("F:/MULTICOREWARE_FTU_INTERN/DEEP_LEARNING_OPERATORS/data/output/max_pooled_feature_maps_2.json", max_pooled_feature_maps_2);

    std::vector<double> flattened_output = performFlattening(max_pooled_feature_maps_2);
    saveToFile("F:/MULTICOREWARE_FTU_INTERN/DEEP_LEARNING_OPERATORS/data/output/flattened_output.json", flattened_output);

    std::string activation_relu = "relu";
    std::vector<double> dense_output_1 = performDense("dense", flattened_output, activation_relu, tensor_ops);
    saveToFile("F:/MULTICOREWARE_FTU_INTERN/DEEP_LEARNING_OPERATORS/data/output/dense_output_1.json", dense_output_1);

    std::string activation_softmax = "softmax";
    std::vector<double> dense_output_2 = performDense("dense_1", dense_output_1, activation_softmax, tensor_ops);
    saveToFile("F:/MULTICOREWARE_FTU_INTERN/DEEP_LEARNING_OPERATORS/data/output/dense_output_2.json", dense_output_2);

    int predicted_number = predictNumber(dense_output_2);
    std::cout << "Predicted number: " << predicted_number << std::endl;
    return 0;
}
