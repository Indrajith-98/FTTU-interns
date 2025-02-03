#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <chrono>
#include "conv2d.h"
#include "max_pooling2d.h"
#include "flatten.h"
#include "dense.h"
#include "file_io.h"
#include "logging.h"
#include "prediction.h"
#include "load_json.h"
#include "relu.h"
#include "testing.h"

int main() {
    
    nlohmann::json config = load_json("/mnt/d/DeepLearningOperators/Configs/json/model_configuration.json");

    const auto& layers = config["layer_details"];

    std::vector<float> input;
    read_image_file("/mnt/d/DeepLearningOperators/ship.png", input);

    for (const auto& layer : layers) {
        
        std::string layer_type = layer["type"];
        std::string layer_name = layer["name"];

        auto start = std::chrono::high_resolution_clock::now();

        if (layer_type == "Conv2D") {
            std::string layer_name = layer["name"];

            std::vector<float> kernel = read_binary_file(layer["weight_files"][0]);
            std::vector<float> bias = read_binary_file(layer["weight_files"][1]);
            
            std::array<int, 4> input_shape = {1, layer["input_shape"][1], layer["input_shape"][2], layer["input_shape"][3]}; 
            std::array<int, 4> output_shape = {1, layer["output_shape"][1], layer["output_shape"][2], layer["output_shape"][3]};
            std::array<int, 2> kernel_size = {layer["kernel_size"][0], layer["kernel_size"][1]};;
            std::array<int, 2> strides = {layer["strides"][0], layer["strides"][1]};;
            std::string padding = layer["padding"]; 
            std::string activation = layer["activation"];
            
            std::vector<float> conv_output(output_shape[1] * output_shape[2] * output_shape[3]); 
            conv2d(input, kernel, bias, conv_output, input_shape, output_shape, kernel_size, strides, padding, layer_name);

            if (activation == "relu") {
            relu(conv_output, layer_name);
            }
            input = conv_output;

            write_output_to_file(input, layer_name);
        } else if (layer_type == "MaxPooling2D") {
            std::string layer_name = layer["name"];
            
            std::array<int, 4> input_shape = {1, layer["input_shape"][1], layer["input_shape"][2], layer["input_shape"][3]}; 
            std::array<int, 4> output_shape = {1, layer["output_shape"][1], layer["output_shape"][2], layer["output_shape"][3]};
            std::array<int, 2> strides = {layer["strides"][0], layer["strides"][1]};;
            std::string padding = layer["padding"]; 

            std::vector<float> maxpool_output(output_shape[1] * output_shape[2] * output_shape[3]);
            max_pooling2d(input, maxpool_output, input_shape, output_shape, {2, 2}, strides, padding, layer_name);

            input = maxpool_output;

            write_output_to_file(input, layer_name);

        } else if (layer_type == "Flatten") {
            std::string layer_name = layer["name"];
            std::array<int, 4> input_shape = {1, layer["input_shape"][1], layer["input_shape"][2], layer["input_shape"][3]};
            std::array<int, 2> output_shape = {1, layer["output_shape"][1]};
            std::vector<float> flatten_output(output_shape[1]);
            flatten(input, flatten_output, input_shape, {output_shape[1]});

            input = flatten_output;

            write_output_to_file(input, layer_name);

        } else if (layer_type == "Dense") {

            std::vector<float> weights = read_binary_file(layer["weight_files"][0]);
            std::vector<float> bias = read_binary_file(layer["weight_files"][1]);

            std::array<int, 2> input_shape = {1, layer["input_shape"][1]};
            std::array<int, 2> output_shape = {1, layer["output_shape"][1]};
            std::string activation = layer["activation"];
            std::string layer_name = layer["name"];

            std::vector<float> dense_output(output_shape[1]);
            dense(input, weights, bias, dense_output, {input_shape[1]}, {output_shape[1]}, activation, layer_name);

            input = dense_output;

            write_output_to_file(input, layer_name);
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        log_execution(layer_name, layer_type, duration.count(), true);

        
    }

    std::string file1 = "/mnt/d/DeepLearningOperators/Data/ref_output/conv2d_3_ref_output.bin";
    std::string file2 = "/mnt/d/DeepLearningOperators/Report/output/conv2d_3_output.bin";

    std::string file3 = "/mnt/d/DeepLearningOperators/Data/ref_output/max_pooling2d_2_ref_output.bin";
    std::string file4 = "/mnt/d/DeepLearningOperators/Report/output/max_pooling2d_2_output.bin";

    std::string file5 = "/mnt/d/DeepLearningOperators/Data/ref_output/conv2d_4_ref_output.bin";
    std::string file6 = "/mnt/d/DeepLearningOperators/Report/output/conv2d_4_output.bin";

    std::string file7 = "/mnt/d/DeepLearningOperators/Data/ref_output/max_pooling2d_3_ref_output.bin";
    std::string file8 = "/mnt/d/DeepLearningOperators/Report/output/max_pooling2d_3_output.bin";

    std::string file9 = "/mnt/d/DeepLearningOperators/Data/ref_output/conv2d_5_ref_output.bin";
    std::string file10 = "/mnt/d/DeepLearningOperators/Report/output/conv2d_5_output.bin";

    std::string file11 = "/mnt/d/DeepLearningOperators/Data/ref_output/flatten_1_ref_output.bin";
    std::string file12 = "/mnt/d/DeepLearningOperators/Report/output/flatten_1_output.bin";

    std::string file13 = "/mnt/d/DeepLearningOperators/Data/ref_output/dense_2_ref_output.bin";
    std::string file14 = "/mnt/d/DeepLearningOperators/Report/output/dense_2_output.bin";

    std::string file15 = "/mnt/d/DeepLearningOperators/Data/ref_output/dense_3_ref_output.bin";
    std::string file16 = "/mnt/d/DeepLearningOperators/Report/output/dense_3_output.bin";

    std::cout<<"~~~~~~~~~~~~Unit Testing~~~~~~~~~~~~~~~~~" << std::endl;
    if (run_test(file1, file2, "conv2d_3")) {
        std::cout << "Test Completed for conv2d_3 layer Successfully." << std::endl;
    } else {
        std::cout << "Files for conv2d_3 layer are significantly different." << std::endl;
    }

    if (run_test(file3, file4, "max_pooling2d_2")) {
        std::cout << "Test Completed for max_pooling2d_2 layer Successfully." << std::endl;
    } else {
        std::cout << "Files for max_pooling2d_2 layer are significantly different." << std::endl;
    }

    if (run_test(file5, file6, "conv2d_4")) {
        std::cout << "Test Completed for conv2d_4 layer Successfully." << std::endl;
    } else {
        std::cout << "Files for conv2d_4 layer are significantly different." << std::endl;
    }

    if (run_test(file7, file8, "max_pooling2d_3")) {
        std::cout << "Test Completed for max_pooling2d_3 layer Successfully." << std::endl;
    } else {
        std::cout << "Files for max_pooling2d_3 layer are significantly different." << std::endl;
    }

    if (run_test(file9, file10, "conv2d_5")) {
        std::cout << "Test Completed for conv2d_5 layer Successfully." << std::endl;
    } else {
        std::cout << "Files for conv2d_5 layer are significantly different." << std::endl;
    }

    if (run_test(file11, file12, "flatten_1")) {
        std::cout << "Test Completed for flatten_1 layer Successfully." << std::endl;
    } else {
        std::cout << "Files for flatten_1 layer are significantly different." << std::endl;
    }

    if (run_test(file13, file14, "dense_2")) {
        std::cout << "Test Completed for dense_2 layer Successfully." << std::endl;
    } else {
        std::cout << "Files for dense_2 layer are significantly different." << std::endl;
    }


    std::cout<<"~~~~~~~~~~~~Model Testing~~~~~~~~~~~~~~~~~" << std::endl;

    if (run_test(file13, file14, "dense_3")) {
        std::cout << "Test Completed for dense_3 (final) layer Successfully." << std::endl;
    } else {
        std::cout << "Files for dense_3(final) layer are significantly different." << std::endl;
    }

    std::string predicted_class = predict_class(input);
    std::cout << "Predicted class " << ": " << predicted_class << std::endl;

    std::cout << "Execution complete, logs saved to execution_log.txt." << std::endl;
    return 0;
}
