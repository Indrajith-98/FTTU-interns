#include "conv.h"
#include "batch_norm.h"
#include "maxpool.h"
#include "dense.h"
#include "utils.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <chrono>
#include "dualstream.h"
#include "test_main.h"

int main() {

    std::string base_dir = "F:/MultiCoreWare/C++ Application/Project_Root/";

    Logger logger(base_dir + "report/log_output.txt");
    
    // Load the configuration file
    std::string json_config_path = "F:/MultiCoreWare/C++ Application/Project_Root/configs/json/layers_config.json";
    nlohmann::json config = load_json_config(json_config_path);
    
    // Load Image
    std::string img_path = "F:/MultiCoreWare/Assignment 1/test_images/test_image_4.jpeg";
    auto input = loadImage(img_path);

    // Ouput Classes
    std::string classes[10] = {"airplane", "automobile", "bird", "cat", "deer", "dog", "frog", "horse", "ship", "truck"};

    // Placeholder for output tensors
    std::vector<float> output;

    // To store predicted class index
    int max_index;

    // Placeholder for input and output shapes
    std::array<int, 4> input_shape{};
    std::array<int, 4> output_shape{};

    for (const auto& layer : config["layers"]) {
        std::string type = layer["type"];
        if (type == "Dropout" || type == "Flatten") continue;
        else std::cout << "Processing Layer: " << layer["layer_name"] << " (" << type << ")" << std::endl;

        if (type == "Conv2D") {

            // Load weights and bias
            auto kernel = load_binary_file(base_dir + std::string(layer["weights_file_paths"][0]));
            auto bias = load_binary_file(base_dir + std::string(layer["weights_file_paths"][1]));

            // Parse shapes and parameters

            input_shape = {
                1,
                layer["attributes"]["input_shape"][1],
                layer["attributes"]["input_shape"][2],
                layer["attributes"]["input_shape"][3]
            };

            output_shape = {
                1,
                layer["attributes"]["output_shape"][1],
                layer["attributes"]["output_shape"][2],
                layer["attributes"]["output_shape"][3]
            };

            std::array<int, 2> kernel_size = {
                layer["attributes"]["kernel_size"][0],
                layer["attributes"]["kernel_size"][1]
            };

            std::array<int, 2> strides = {
                layer["attributes"]["strides"][0],
                layer["attributes"]["strides"][1]
            };

            std::string padding = layer["attributes"]["padding"];

            std::cout << "InputSize = " << input.size() << std::endl;
            std::cout << "KernelSize = " << kernel.size() << std::endl;
            std::cout << "BiasSize = " << bias.size() << std::endl;

            // Allocate memory for the output tensor
            output.resize(output_shape[1] * output_shape[2] * output_shape[3]);

            auto start = std::chrono::high_resolution_clock::now();

            // Perform the Conv2D operation
            conv2d(input, kernel, bias, output, input_shape, output_shape, kernel_size, strides, padding, layer["layer_name"]);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_time = end - start;
            std::cout << "Execution time: " << elapsed_time.count() * 100 << " ms" << std::endl;

        } else if (type == "BatchNormalization") {

            // Load gamma, beta, moving_mean, and moving_variance
            auto gamma = load_binary_file(base_dir + std::string(layer["weights_file_paths"][0]));
            auto beta = load_binary_file(base_dir + std::string(layer["weights_file_paths"][1]));
            auto moving_mean = load_binary_file(base_dir + std::string(layer["weights_file_paths"][2]));
            auto moving_variance = load_binary_file(base_dir + std::string(layer["weights_file_paths"][3]));

            // Epsilon value for numerical stability
            float epsilon = 0.001;

            std::cout << "Input size: " << input.size() << std::endl;
            std::cout << "Gamma size: " << gamma.size() << std::endl;
            std::cout << "Beta size: " << beta.size() << std::endl;
            std::cout << "Moving Mean size: " << moving_mean.size() << std::endl;
            std::cout << "Moving Variance size: " << moving_variance.size() << std::endl;

            input_shape = {
                1,
                layer["attributes"]["input_shape"][1],
                layer["attributes"]["input_shape"][2],
                layer["attributes"]["input_shape"][3]
            };

            output_shape = {
                1,
                layer["attributes"]["output_shape"][1],
                layer["attributes"]["output_shape"][2],
                layer["attributes"]["output_shape"][3]
            };

            output.resize(output_shape[1] * output_shape[2] * output_shape[3]);

            auto start = std::chrono::high_resolution_clock::now();

            // Perform the BatchNormalization operation
            batch_normalization(input, output, gamma, beta, moving_mean, moving_variance, epsilon,output_shape[3], input_shape[1], input_shape[2], layer["layer_name"]);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_time = end - start;
            std::cout << "Execution time: " << elapsed_time.count() * 100 << " ms" << std::endl;

        } else if (type == "MaxPooling2D") {

            // Parse shapes and parameters
            input_shape = {
                1,
                layer["attributes"]["input_shape"][1],
                layer["attributes"]["input_shape"][2],
                layer["attributes"]["input_shape"][3]
            };
            output_shape = {
                1,
                layer["attributes"]["output_shape"][1],
                layer["attributes"]["output_shape"][2],
                layer["attributes"]["output_shape"][3]
            };
            std::array<int, 2> pool_size = {
                2,
                2
            };
            std::array<int, 2> strides = {
                layer["attributes"]["strides"][0],
                layer["attributes"]["strides"][1]
            };
            std::string padding = layer["attributes"]["padding"];

            std::cout << "InputSize = " << input.size() << std::endl;

            // Allocate memory for the output tensor
            output.resize(output_shape[1] * output_shape[2] * output_shape[3]);

            auto start = std::chrono::high_resolution_clock::now();

            // Perform the MaxPooling2D operation
            max_pooling2d(input, output, input_shape, output_shape, pool_size, strides, padding, layer["layer_name"]);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_time = end - start;
            std::cout << "Execution time: " << elapsed_time.count() * 100 << " ms" << std::endl;

        } else if (type == "Dense") {

            // Load weights and bias
            auto weights = load_binary_file(base_dir + std::string(layer["weights_file_paths"][0]));
            auto bias = load_binary_file(base_dir + std::string(layer["weights_file_paths"][1]));

            // Parse shapes and parameters
            std::array<int, 2> dense_input_shape = {
                1,
                layer["attributes"]["input_shape"][1]
            };
            std::array<int, 2> dense_output_shape = {
                1,
                layer["attributes"]["output_shape"][1]
            };
            std::string activation = layer["attributes"]["activation"];

            // Allocate memory for the output tensor
            output.resize(dense_output_shape[1]);

            auto start = std::chrono::high_resolution_clock::now();
            
            // Perform the Dense operation
            dense(input, weights, bias, output, dense_input_shape, dense_output_shape, activation, layer["layer_name"]);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_time = end - start;
            std::cout << "Execution time: " << elapsed_time.count() * 100 << " ms" << std::endl;

        }

        input = output;

        std::cout << "=======================================================================" << std::endl;
    }

    // Display the predicted class
    auto max_elem = std::max_element(output.begin(), output.end());
    max_index = std::distance(output.begin(), max_elem);
    
    std::cout << "Max value: " << *max_elem << " at index " << max_index << std::endl;
    std::cout << "Predicted Class: " << classes[max_index] << std::endl;
    std::cout << "Processing completed successfully!" << std::endl;

    std::cerr << "=======================================================================" << std::endl;

    std::cerr << "Unit Test Begins" << std::endl;
    unit_test();
    std::cerr << "Unit Test Ends" << std::endl;
    
    std::cerr << "=======================================================================" << std::endl;

    std::cerr << "Model Test Begins" << std::endl;
    model_test();
    std::cerr << "Model Test Ends" << std::endl;

    std::cerr << "=======================================================================" << std::endl;
    
    return 0;
}