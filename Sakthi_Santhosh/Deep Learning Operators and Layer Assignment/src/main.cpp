#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "nlohmann/json.hpp"
#include "conv2d.h"
#include "maxpooling.h"
#include "dense.h"
#include "flatten.h"

nlohmann::json load_json_config(const std::string& file_path) {
    std::ifstream config_file(file_path);
    if (!config_file.is_open()) {
        std::cerr << "Error: Unable to open config file: " << file_path << std::endl;
        exit(EXIT_FAILURE);
    }
    nlohmann::json config;
    config_file >> config;
    return config;
}

bool readImageAsVector(const std::string& imagePath, std::vector<float>& outputVector) {
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image: " << imagePath << std::endl;
        return false;
    }
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    cv::resize(image, image, cv::Size(32, 32));
    outputVector.clear();
    for (int row = 0; row < image.rows; ++row) {
        for (int col = 0; col < image.cols; ++col) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(row, col);
            outputVector.push_back(pixel[0] / 255.0f);
            outputVector.push_back(pixel[1] / 255.0f);
            outputVector.push_back(pixel[2] / 255.0f);
        }
    }
    return true;
}

void save_output_as_txt(const std::string& layer_name, const std::vector<float>& data) {
    std::string output_dir = "D:/Santhosh@McW/DL_Inference/Output";
    std::filesystem::create_directories(output_dir);
    std::string file_path = output_dir + "/" + layer_name + "_output.txt";
    std::ofstream out_file(file_path);
    if (!out_file.is_open()) {
        std::cerr << "Error: Unable to write to file: " << file_path << std::endl;
        return;
    }
    for (float val : data) {
        out_file << val << " ";
    }
    out_file << std::endl;
}

std::vector<float> load_binary_file(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open binary file: " + file_path);
    }
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    if (size == 0) {
        throw std::runtime_error("Error: The file is empty: " + file_path);
    }
    file.seekg(0, std::ios::beg);
    std::vector<float> data(size / sizeof(float));
    file.read(reinterpret_cast<char*>(data.data()), size);
    return data;
}

int main() {
    std::string config_path = "D:/layer_config.json";
    nlohmann::json config = load_json_config(config_path);
    
    std::vector<float> input_data;
    std::string image_path = "D:/Santhosh@McW/DL_Inference/image.jpg";
    if (!readImageAsVector(image_path, input_data)) {
        return EXIT_FAILURE;
    }
    
    for (const auto& layer : config) {
        std::string layer_type = layer["type"];
        std::string layer_name = layer["layer_name"];
        
        if (layer_type == "Conv2D") {
            std::vector<float> kernel = load_binary_file(layer["weight_file_paths"][0]);
            std::vector<float> bias = load_binary_file(layer["weight_file_paths"][1]);
            
            std::array<int, 4> input_shape = {1, layer["attributes"]["input_shape"][0], layer["attributes"]["input_shape"][1], layer["attributes"]["input_shape"][2]};
            std::array<int, 4> output_shape = {1, layer["attributes"]["output_shape"][0], layer["attributes"]["output_shape"][1], layer["attributes"]["output_shape"][2]};
            
            // Convert JSON arrays for kernel_size and strides into std::array<int, 2>
            std::array<int, 2> kernel_size = {layer["attributes"]["kernel_size"][0], layer["attributes"]["kernel_size"][1]};
            std::array<int, 2> strides = {layer["attributes"]["strides"][0], layer["attributes"]["strides"][1]};
        
            
            std::vector<float> conv_output(output_shape[1] * output_shape[2] * output_shape[3]);
             conv2d(input_data, kernel, bias, conv_output, 
                   input_shape, output_shape, kernel_size, strides, layer["attributes"]["padding"], layer_name);
            input_data = std::move(conv_output);
            save_output_as_txt(layer_name, input_data);
            std::cout << "Convolution operation completed for layer: " << layer_name << std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
        }

        else if (layer_type == "MaxPooling2D") {
            std::array<int, 4> input_shape = {1, layer["attributes"]["input_shape"][0], layer["attributes"]["input_shape"][1], layer["attributes"]["input_shape"][2]};
            std::array<int, 4> output_shape = {1, layer["attributes"]["output_shape"][0], layer["attributes"]["output_shape"][1], layer["attributes"]["output_shape"][2]};
            
            // Assuming pool_size and strides are the same for MaxPooling2D
            std::array<int, 2> pool_size = {2, 2}; // Typical pool size
            std::array<int, 2> strides = {1, 1};  // Typical stride size
            
            std::vector<float> maxpool_output(output_shape[1] * output_shape[2] * output_shape[3]);
            max_pooling2d(input_data, maxpool_output, input_shape, output_shape, pool_size, strides, layer_name);

            // void maxpooling(const std::vector<float>& input, std::vector<float>& output,
            //     const std::array<int, 4>& input_shape, const std::array<int, 4>& output_shape,
            //     const std::array<int, 2>& pool_size, const std::array<int, 2>& strides,
            //     const std::string& layer_name)

            input_data = std::move(maxpool_output);
            save_output_as_txt(layer_name, input_data);
            std::cout << "Convolution operation completed for layer: " << layer_name << std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
        }
        else if (layer_type == "Dense") {
            std::vector<float> weights = load_binary_file(layer["weight_file_paths"][0]);
            std::vector<float> bias = load_binary_file(layer["weight_file_paths"][1]);
            
            std::array<int, 2> input_shape = {1, layer["attributes"]["input_shape"][0]};
            std::array<int, 2> output_shape = {1, layer["attributes"]["output_shape"][0]};
            
            std::vector<float> dense_output(output_shape[1]);
            dense(input_data, weights, bias, dense_output, input_shape, output_shape, layer_name, "relu");
            input_data = std::move(dense_output);
            save_output_as_txt(layer_name, input_data);
            std::cout << "Convolution operation completed for layer: " << layer_name << std::endl;
            std::cout<<input_data.size()<<std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
        }
        else if (layer_type == "Flatten") {
    
    std::array<int, 4> input_shape = {
        1,
        layer["attributes"]["input_shape"][0],
        layer["attributes"]["input_shape"][1],
        layer["attributes"]["input_shape"][2]
    };

    // The output is a 1D vector whose length equals the product of the 4D dimensions.
    std::vector<float> flatten_output;
    
    // Call flatten with the 4D input shape.
    flatten(input_data, input_shape, flatten_output);
    
    // Move the flattened result back to input_data for the next layer.
    input_data = std::move(flatten_output);
    
    // Save the flattened output as text.
    save_output_as_txt(layer_name, input_data);

    
    std::cout << "Flatten operation completed for layer: " << layer_name << std::endl;
    std::cout << std::endl << std::endl;
}

    }
    
    save_output_as_txt("final_output", input_data);
    return EXIT_SUCCESS;
}
