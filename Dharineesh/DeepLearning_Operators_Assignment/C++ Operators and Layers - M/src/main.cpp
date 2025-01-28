#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include<nlohmann/json.hpp>
#include <vector>
#include <cstdint>
#include "../Operators/include/Conv2D.h"
#include "../include/MaxPooling2D.h"
#include "Flatten.h"
#include "DenseLayer.h"
#include "BatchNormalization.h"
#include "utils.h"
#include "unit_test.h"
#include <array>
using json = nlohmann::json;


void first_channel_output(std::vector<float> output,std::array<int, 4> output_shape,std::string layername){


    
            std::cout << layername <<" layer Values :\n";
                int output_height = output_shape[1];
                int output_width = output_shape[2];
                int num_channels = output_shape[3];

                std::cout<<"Output Height: "<<output_height<<std::endl;
                std::cout<<"Output Width: "<<output_width<<std::endl;
                std::cout<<"Number of Channels: "<<num_channels<<std::endl;

               for (int i = 0; i < output_height; ++i) {
                    for (int j = 0; j < output_width; ++j) {
                        // Calculate the index for the first channel
                        int index = (i * output_width + j) * num_channels;  // For first channel (channel 0)

                        // Access and print the first channel value at [i][j]
                        std::cout << output[index] << " ";  // Print the value for the first channel
                    }
                    std::cout << std::endl;  // New line after each row
                }
}


void first_channel_output_dense(std::vector<float> output){
    std::cout << "First 10  Values of Dense layer:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << output[i] << " ";
    }
    std::cout << std::endl;
}
int main()
{


    std::ifstream configFile("O:/C++ Operators and Layers - M/configs/json/HyperParameterConfigurationFile.json");
    if (!configFile.is_open()) {
        std::cout<< "Failed to open configuration file.\n";
        return 1;
    }
    int c=0;
    json config;
    configFile >> config;

     std::string inputPath = "O:/C++ Operators and Layers - M/sample_image.bin";
    std::vector<float> input;
     input = readBinaryFile<float>(inputPath);

    // Ouput Classes
    std::string classes[10] = {"airplane", "automobile", "bird", "cat", "deer", "dog", "frog", "horse", "ship", "truck"};

    std::vector<float> output;

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
            auto kernel = load_binary_file(layer["weights_file_paths"][0]);
            auto bias = load_binary_file(layer["weights_file_paths"][1]);

            // Parse shapes and parameters

            input_shape = {1,layer["attributes"]["input_shape"][0],layer["attributes"]["input_shape"][1],layer["attributes"]["input_shape"][2]};

            output_shape = {1,layer["attributes"]["output_shape"][0],layer["attributes"]["output_shape"][1],layer["attributes"]["output_shape"][2]};

            std::array<int, 2> kernel_size = {layer["attributes"]["kernel_size"][0],layer["attributes"]["kernel_size"][1]};

            std::array<int, 2> strides = {layer["attributes"]["strides"][0],layer["attributes"]["strides"][1]};

            std::string padding = layer["attributes"]["padding"];

            std::cout << "InputSize = " << input.size() << std::endl;
            std::cout << "KernelSize = " << kernel.size() << std::endl;
            std::cout << "BiasSize = " << bias.size() << std::endl;

            // Allocate memory for the output tensor
            output.resize(output_shape[1] * output_shape[2] * output_shape[3]);

            // Perform the Conv2D operation
           
            conv2d(input, kernel, bias, output, input_shape, output_shape, kernel_size, strides, padding, layer["layer_name"]);
            input=output;
            first_channel_output(output,output_shape,layer["layer_name"]);

            

        } 
        else if (type == "BatchNormalization") {

            // Load gamma, beta, moving_mean, and moving_variance
            auto gamma =load_binary_file( layer["weights_file_paths"][0]);
            auto beta =load_binary_file( layer["weights_file_paths"][1]);
            auto moving_mean =load_binary_file( layer["weights_file_paths"][2]);
            auto moving_variance = load_binary_file(layer["weights_file_paths"][3]);

            // Epsilon value for numerical stability
            float epsilon = 0.001;

            std::cout << "Input size: " << input.size() << std::endl;
            std::cout << "Gamma size: " << gamma.size() << std::endl;
            std::cout << "Beta size: " << beta.size() << std::endl;
            std::cout << "Moving Mean size: " << moving_mean.size() << std::endl;
            std::cout << "Moving Variance size: " << moving_variance.size() << std::endl;

            input_shape = {1,layer["attributes"]["input_shape"][0],layer["attributes"]["input_shape"][1],layer["attributes"]["input_shape"][2] };

            output_shape = {1,layer["attributes"]["output_shape"][0],layer["attributes"]["output_shape"][1],layer["attributes"]["output_shape"][2]};

            output.resize(output_shape[1] * output_shape[2] * output_shape[3]);

            // Perform the BatchNormalization operation
            batch_normalization(input, output, gamma, beta, moving_mean, moving_variance, epsilon,output_shape[3], input_shape[1], input_shape[2], layer["layer_name"]);
            input = output;

            first_channel_output(output,output_shape,layer["layer_name"]);
        } 
    else if (type == "MaxPooling2D") {

            // Parse shapes and parameters
            input_shape = {1,layer["attributes"]["input_shape"][0],layer["attributes"]["input_shape"][1],layer["attributes"]["input_shape"][2]};
            output_shape = {1,layer["attributes"]["output_shape"][0],layer["attributes"]["output_shape"][1],layer["attributes"]["output_shape"][2]};
            
            std::array<int, 2> pool_size = {2,2};

            std::array<int, 2> strides = { layer["attributes"]["strides"][0],layer["attributes"]["strides"][1]};
            std::string padding = layer["attributes"]["padding"];

            std::cout << "InputSize = " << input.size() << std::endl;

            // Allocate memory for the output tensor
            output.resize(output_shape[1] * output_shape[2] * output_shape[3]);

            // Perform the MaxPooling2D operation
            max_pooling2d(input, output, input_shape, output_shape, pool_size, strides, padding, layer["layer_name"]);
            input=output;


             first_channel_output(output,output_shape,layer["layer_name"]);

        } 
        else if (type == "Dense") {

            // Load weights and bias
            auto weights = load_binary_file(layer["weights_file_paths"][0]);
            auto bias = load_binary_file(layer["weights_file_paths"][1]);

            // Parse shapes and parameters
            std::array<int, 2> dense_input_shape = {1, layer["attributes"]["input_shape"][0]};
            std::array<int, 2> dense_output_shape = {1, layer["attributes"]["output_shape"][0] };
            std::string activation = layer["attributes"]["activation"];

            // Allocate memory for the output tensor
            output.resize(dense_output_shape[1]);

            
            // Perform the Dense operation
            dense(input, weights, bias, output, dense_input_shape, dense_output_shape, activation, layer["layer_name"]);
            input=output;
            first_channel_output_dense(input);
        }

        std::cout << "\n\n" << std::endl;
    }

    // // Display the predicted class
    auto max_elem = std::max_element(output.begin(), output.end());
    max_index = std::distance(output.begin(), max_elem);
    
    std::cout << "Max value: " << *max_elem << " at index " << max_index << std::endl;
    std::cout << "Predicted Class: " << classes[max_index] << std::endl;




    std::cout<<"------------------------Unit Test------------------------" << std::endl;
        std::string output_file1 = "O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/conv2d.txt";
        std::string expected_file1 = "O:/C++ Operators and Layers - M/LayerWiseOutput/PythonLayerWiseOutput/conv2d_output.txt";
        std::string output_file4 = "O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/batch_normalization.txt";
        std::string expected_file4 = "O:/C++ Operators and Layers - M/LayerWiseOutput/PythonLayerWiseOutput/batch_normalization_output.txt";
        std::string output_file9 = "O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/max_pooling2d.txt";
        std::string expected_file9 = "O:/C++ Operators and Layers - M/LayerWiseOutput/PythonLayerWiseOutput/max_pooling2d_output.txt";
        std::string output_file2 = "O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/conv2d_1.txt";
        std::string expected_file2 = "O:/C++ Operators and Layers - M/LayerWiseOutput/PythonLayerWiseOutput/conv2d_1_output.txt";
        std::string output_file5 = "O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/batch_normalization_1.txt";
        std::string expected_file5 = "O:/C++ Operators and Layers - M/LayerWiseOutput/PythonLayerWiseOutput/batch_normalization_1_output.txt";
        std::string output_file8 = "O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/max_pooling2d_1.txt";
        std::string expected_file8 = "O:/C++ Operators and Layers - M/LayerWiseOutput/PythonLayerWiseOutput/max_pooling2d_1_output.txt";
        std::string output_file3 = "O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/conv2d_2.txt";
        std::string expected_file3 = "O:/C++ Operators and Layers - M/LayerWiseOutput/PythonLayerWiseOutput/conv2d_2_output.txt";
        std::string output_file6 = "O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/batch_normalization_2.txt";
        std::string expected_file6 = "O:/C++ Operators and Layers - M/LayerWiseOutput/PythonLayerWiseOutput/batch_normalization_2_output.txt";
        std::string output_file10 = "O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/dense.txt";
        std::string expected_file10 = "O:/C++ Operators and Layers - M/LayerWiseOutput/PythonLayerWiseOutput/dense_output.txt";
        std::string output_file11 = "O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/dense_1.txt";
        std::string expected_file11 = "O:/C++ Operators and Layers - M/LayerWiseOutput/PythonLayerWiseOutput/dense_1_output.txt";


        // Compare the files
        unit_test("conv1",output_file1, expected_file1);
        unit_test("batch_norm1",output_file4, expected_file4);
        unit_test("max_pool1",output_file9, expected_file9);
        unit_test("conv2",output_file2, expected_file2);
        unit_test("batch_norm2",output_file5, expected_file5);
        unit_test("max_pool2",output_file8, expected_file8);
        unit_test("conv3",output_file3, expected_file3);
        unit_test("batch_norm3",output_file6, expected_file6);
        unit_test("dense1",output_file10, expected_file10);
        unit_test("dense2",output_file11, expected_file11);

        std::cout <<"------------------------Unit Test Ends------------------------";
    
    return 0;
}

