#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "utils.h"
#include "convolution.h"
#include "dense.h"
#include "maxpool.h"
#include "flatten.h"
#include "relu.h"
#include "softmax.h"

using json = nlohmann::json;

json loadModelConfig(const std::string& configPath) {
    std::ifstream file(configPath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << configPath << std::endl;
        exit(EXIT_FAILURE);
    }
    json config;
    file >> config;
    return config;
}

int main() {
    std::string configPath = "D:/Multicoreware/Assignments/Z-Final_OP/configs/json/model_config.json";
    json modelConfig = loadModelConfig(configPath);

    std::cout << "Loaded JSON:\n" << modelConfig.dump(4) << std::endl;

    std::cout << "Loaded Model: " << modelConfig["layers"].size() << " layers found.\n";

    for (const auto& layer : modelConfig["layers"]) {
        if (!layer.contains("type")) {
            std::cerr << "Error: Missing 'type' field in model_config.json" << std::endl;
            continue;
        }
        std::string layerType = layer["type"];

        if (!layer.contains("input_file_path") || !layer.contains("output_file_path")) {
            std::cerr << "Error: Missing 'input_file_path' or 'output_file_path' in " << layerType << " layer." << std::endl;
            continue;
        }

        std::string inputPath = layer["input_file_path"];
        std::string outputPath = layer["output_file_path"];

        std::vector<std::string> weightPaths;
        if (layer.contains("weights_file_paths")) {
            weightPaths = layer["weights_file_paths"].get<std::vector<std::string>>();
        }

        // Process each layer type
        if (layerType == "Conv2D") {
            Convolution convLayer(layer);
            convLayer.forward(inputPath, weightPaths, outputPath);
            // Apply ReLU activation function after Conv2D layer
            ReLU reluActivation;
            reluActivation.forward(outputPath, outputPath);
        } else if (layerType == "MaxPooling2D") {
            int pool_size = layer["attributes"]["pool_size"];
            MaxPooling2D maxpoolLayer(pool_size);
            maxpoolLayer.forward(inputPath, outputPath);
        } else if (layerType == "Dense") {
            Dense denseLayer(layer);
            denseLayer.forward(inputPath, weightPaths, outputPath);
            // Apply ReLU activation function after Dense layer
            ReLU reluActivation;
            reluActivation.forward(outputPath, outputPath);
        } else if (layerType == "Flatten") {
            Flatten flattenLayer;
            flattenLayer.forward(inputPath, outputPath);
        } else if (layerType == "Softmax") {
            Softmax softmaxActivation;
            softmaxActivation.forward(outputPath, outputPath);
        } else {
            std::cerr << "Unsupported layer: " << layerType << std::endl;
        }
    }

    std::cout << "Execution completed!" << std::endl;
    std::vector<std::string> labels = {"Airplane", "Automobile", "Bird", "Cat", "Deer",
                                       "Dog", "Frog", "Horse", "Ship", "Truck"};

    // Find the index of the maximum value
        auto max_iter = std::max_element(layer_output.begin(), layer_output.end());
        int predicted_index = std::distance(layer_output.begin(), max_iter);

        // Predict the class
        std::string predicted_class = labels[predicted_index];

        // Print the prediction
        std::cout << "Predicted class: " << predicted_class << " (Index: " << predicted_index << ")" << std::endl;

        std::ofstream outfile("F:/MCW/c++ application/Project_Root/report/model_prediction_output.txt",std::ios::app);
        if (outfile.is_open()) {
            outfile << "Predicted class at cpp: " << predicted_class << " (Index: " << predicted_index << ")" << std::endl;
            cout << "=====================================================\n";
            outfile.close();
        } else {
            std::cerr << "Error opening file for writing!" << std::endl;
        }

        cout<<"Unit Test Begins" << endl;
        std::string output_file1 = "D:/Multicoreware/Assignments/Z-Final_OP/data/cpp_outputs/conv2d_1_output.txt";
        std::string expected_file1 = "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/conv2d_1_output.txt";
        std::string output_file4 ="D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/conv2d_2_output.txt";
        std::string expected_file4 = "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/conv2d_2_output.txt";
        std::string output_file9 =  "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/conv2d_output.txt";
        std::string expected_file9 = "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/conv2d_output.txt";
        std::string output_file2 = "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/dense_1_output.txt";
        std::string expected_file2 = "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/dense_1_output.txt";
        std::string output_file5 ="D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/dense_output.txt";
        std::string expected_file5 = "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/dense_output.txt";
        std::string output_file8 = "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/flatten_output.txt";
        std::string expected_file8 = "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/flatten_output.txt";
        std::string output_file3 = "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/max_pooling2d_1_output.txt";
        std::string expected_file3 = "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/max_pooling2d_1_output.txt";
        std::string output_file6 =  "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/max_pooling2d_2_output.txt";
        std::string expected_file6 = "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/max_pooling2d_2_output.txt";
        std::string output_file10 = "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/max_pooling2d_output.txt";
        std::string expected_file10 = "D:/Multicoreware/Assignments/Z-Final_OP/data/python_outputs/max_pooling2d_output.txt";
        

        // Compare the files
        unittest("conv1",output_file1, expected_file1);
        unittest("conv2",output_file4, expected_file4);
        unittest("conv3",output_file9, expected_file9);
        unittest("dense1",output_file2, expected_file2);
        unittest("dense2",output_file5, expected_file5);
        unittest("flatten",output_file8, expected_file8);
        unittest("maxpooling1",output_file3, expected_file3);
        unittest("maxpooling2",output_file6, expected_file6);
        unittest("maxpooling3",output_file10, expected_file10);
        

        cout <<"Unit Test Ends";

        return 0;
}
