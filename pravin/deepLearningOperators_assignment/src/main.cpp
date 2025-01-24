#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include <string>
#include <cassert>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <cmath>

// Function declarations
void conv2d(const std::vector<float>& input, const std::vector<float>& kernel, const std::vector<float>& bias,
            std::vector<float>& output, const std::array<int, 4>& input_shape, const std::array<int, 4>& output_shape,
            const std::array<int, 2>& kernel_size, const std::array<int, 2>& strides, const std::string& padding, const std::string& layer_name);

void dense(const std::vector<float>& input, const std::vector<float>& weights, const std::vector<float>& bias,
           std::vector<float>& output, const std::array<int, 2>& input_shape, const std::array<int, 2>& output_shape,
           const std::string& activation, const std::string layer_name);

void max_pooling2d(const std::vector<float>& input, std::vector<float>& output,
                   const std::array<int, 4>& input_shape, const std::array<int, 4>& output_shape,
                   const std::array<int, 2>& pool_size, const std::array<int, 2>& strides,
                   const std::string& padding, const std::string& layer_name);

void relu(std::vector<float>& tensor);
void softmax(std::vector<float>& tensor);

nlohmann::json load_json_config(const std::string& config_path) {
    std::ifstream config_file(config_path);
    if (!config_file) {
        throw std::runtime_error("Failed to open config file: " + config_path);
    }
    return nlohmann::json::parse(config_file);
}

std::vector<float> load_binary_file(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open binary file: " + file_path);
    }
    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<float> buffer(file_size / sizeof(float));
    file.read(reinterpret_cast<char*>(buffer.data()), file_size);
    return buffer;
}

void save_output_as_txt(const std::string& layer_name, const std::vector<float>& output) {
    std::ofstream file("Output/cpp/" + layer_name + "_output.txt");
    if (!file) {
        throw std::runtime_error("Failed to save output for layer: " + layer_name);
    }
    for (float val : output) {
        file << val << "\n";
    }
}

void readImageAsVector(const std::string& image_path, std::vector<float>& input_data) {
    std::ifstream image_file(image_path, std::ios::binary);
    if (!image_file) {
        throw std::runtime_error("Failed to open image file: " + image_path);
    }
    float pixel;
    while (image_file >> pixel) {
        input_data.push_back(pixel / 255.0f); // Normalize to range [0, 1]
    }
}

void predict_and_print_class(const std::vector<float>& logits) {
    auto max_iter = std::max_element(logits.begin(), logits.end());
    int predicted_class = std::distance(logits.begin(), max_iter);
    std::cout << predicted_class << std::endl;
}

void compare_model_outputs(const std::string& cpp_output, const std::string& python_output) {
    std::ifstream cpp_file(cpp_output), python_file(python_output);
    if (!cpp_file || !python_file) {
        throw std::runtime_error("Failed to open output files for comparison.");
    }

    float cpp_val, python_val;
    bool match = true;
    while (cpp_file >> cpp_val && python_file >> python_val) {
        if (std::abs(cpp_val - python_val) > 1e-5) {
            match = false;
            break;
        }
    }
    if (match) {
        std::cout << "Model outputs match!" << std::endl;
    } else {
        std::cout << "Model outputs do not match!" << std::endl;
    }
}

void compare_directories(const std::string& dir1, const std::string& dir2) {
    // This would require directory traversal logic, potentially using `filesystem` in C++17.
    std::cout << "Directory comparison logic is currently a placeholder." << std::endl;
}

int main() {
    std::string config_path = "/Users/pravinpb/pycode/MCW/Assignments/cifar10-cpp/configs/json/model_config.json";
    nlohmann::json config = load_json_config(config_path);

    std::string python_dir = "/Users/pravinpb/pycode/MCW/Assignments/cifar10-cpp/Output/python";
    std::string cpp_dir = "/Users/pravinpb/pycode/MCW/Assignments/cifar10-cpp/Output/cpp";

    std::string cpp_output_file = "/Users/pravinpb/pycode/MCW/Assignments/cifar10-cpp/Output/cpp/dense_1_output.txt";
    std::string python_output_file = "/Users/pravinpb/pycode/MCW/Assignments/cifar10-cpp/Output/python/dense_1_output.txt";

    std::vector<float> input_data;
    readImageAsVector("/Users/pravinpb/pycode/MCW/Assignments/cifar10-cpp/toTest/images/0001_9.png", input_data);

    for (const auto& layer : config["layers"]) {
        std::string layer_type = layer["type"];
        if (layer_type == "Conv2D") {
            std::vector<float> kernel = load_binary_file(layer["weights_file_paths"][0]);
            std::vector<float> bias = load_binary_file(layer["weights_file_paths"][1]);
            std::array<int, 4> input_shape = {1, layer["attributes"]["input_shape"][0], layer["attributes"]["input_shape"][1], layer["attributes"]["input_shape"][2]};
            std::array<int, 4> output_shape = {1, layer["attributes"]["output_shape"][0], layer["attributes"]["output_shape"][1], layer["attributes"]["output_shape"][2]};
            std::array<int, 2> kernel_size = {layer["attributes"]["kernel_size"][0], layer["attributes"]["kernel_size"][1]};
            std::array<int, 2> strides = {layer["attributes"]["strides"][0], layer["attributes"]["strides"][1]};
            std::string padding = layer["attributes"]["padding"];
            std::string activation = layer["attributes"]["activation"];

            std::vector<float> conv_output(output_shape[1] * output_shape[2] * output_shape[3]);
            conv2d(input_data, kernel, bias, conv_output, input_shape, output_shape, kernel_size, strides, padding, layer["layer_name"]);

            if (activation == "relu") {
                relu(conv_output);
            }
            input_data = conv_output;
            save_output_as_txt(layer["layer_name"], input_data);
        } else if (layer_type == "MaxPooling2D") {
            std::array<int, 4> input_shape = {1, layer["attributes"]["input_shape"][0], layer["attributes"]["input_shape"][1], layer["attributes"]["input_shape"][2]};
            std::array<int, 4> output_shape = {1, layer["attributes"]["output_shape"][0], layer["attributes"]["output_shape"][1], layer["attributes"]["output_shape"][2]};
            std::array<int, 2> pool_size = {layer["attributes"]["pool_size"][0], layer["attributes"]["pool_size"][1]};
            std::array<int, 2> strides = {layer["attributes"]["strides"][0], layer["attributes"]["strides"][1]};
            std::string padding = layer["attributes"]["padding"];
            std::string layer_name = layer["layer_name"];

            std::vector<float> maxpool_output(output_shape[1] * output_shape[2] * output_shape[3]);
            max_pooling2d(input_data, maxpool_output, input_shape, output_shape, pool_size, strides, padding, layer_name);

            input_data = maxpool_output;
            save_output_as_txt(layer["layer_name"], input_data);
        } else if (layer_type == "Dense") {
            std::vector<float> weights = load_binary_file(layer["weights_file_paths"][0]);
            std::vector<float> bias = load_binary_file(layer["weights_file_paths"][1]);
            std::array<int, 2> input_shape = {1, layer["attributes"]["input_shape"][0]};
            std::array<int, 2> output_shape = {1, layer["attributes"]["output_shape"][0]};
            std::string activation = layer["attributes"]["activation"];
            std::string layer_name = layer["layer_name"];

            std::vector<float> dense_output(output_shape[1]);
            dense(input_data, weights, bias, dense_output, input_shape, output_shape, activation, layer_name);

            input_data = dense_output;
            save_output_as_txt(layer_name, input_data);
        }
    }

    std::cout << "Final output size: " << input_data.size() << std::endl;
    predict_and_print_class(input_data);

    std::cout << "Unit Testing" << std::endl;
    compare_directories(python_dir, cpp_dir);

    std::cout << "Model Testing" << std::endl;
    compare_model_outputs(cpp_output_file, python_output_file);

    return 0;
}
