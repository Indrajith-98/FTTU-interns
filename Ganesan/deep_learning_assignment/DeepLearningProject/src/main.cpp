#include <iostream>
#include <fstream>
#include <chrono> // For timing execution
#include <nlohmann/json.hpp>
#include <vector>
#include "file_io.h"
#include "relu.h"
#include "maxpool.h"
#include "softmax.h"
#include "conv.h"
#include "add.h"
#include "matmul.h"

// Function to save layer outputs for debugging
void save_layer_dump(const std::string &layer_name, const std::vector<float> &data, const std::string &file_type)
{
    std::string filename = "../data/output/" + layer_name + "_" + file_type + ".bin";
    write_binary_file(filename, data);
}

// Function to log execution details (with time measurement)
void log_execution(const std::string &layer_name, const std::string &function, double execution_time, bool status)
{
    std::ofstream log_file("../report/execution_log.txt", std::ios::app);
    std::string pass_fail = status ? "Pass" : "Fail";

    std::string log_message = "Layer: " + layer_name + "\n" +
                              "Function Executed: " + function + "\n" +
                              "Execution Time: " + std::to_string(execution_time) + " seconds\n" +
                              "Pass/Fail: " + pass_fail + "\n";

    if (log_file)
    {
        log_file << log_message << std::endl;
    }
    std::cout << log_message << std::endl;
}

int main()
{
    std::ifstream file("../configs/json/config.json");
    if (!file)
    {
        std::cerr << "ERROR: Failed to open config.json!" << std::endl;
        return 1;
    }

    nlohmann::json config;
    file >> config;
    std::cout << "JSON file loaded successfully!" << std::endl;

    std::vector<float> prev_output; // Store previous layer output dynamically

    for (const auto &layer : config["layers"])
    {
        std::string layer_name = layer["name"];
        std::string layer_type = layer["type"];

        std::cout << "Executing Layer: " << layer_name << " (" << layer_type << ")" << std::endl;

        // Read input data (first layer from file, others use prev_output)
        std::vector<float> input_data = prev_output.empty() ? read_binary_file("../data/input/" + layer_name + "_input.bin") : prev_output;
        if (input_data.empty())
        {
            std::cerr << "ERROR: Failed to read input data for " << layer_name << std::endl;
            return 1;
        }

        std::vector<float> output_data;
        auto start_time = std::chrono::high_resolution_clock::now(); // Start timing

        // Execute different layer operations
        if (layer_type == "Conv")
        {
            int input_size = 32, stride = 1, padding = 1, kernel_size = 3;
            std::vector<float> weights(kernel_size * kernel_size, 1.0f);
            conv(input_data, weights, output_data, input_size, stride, padding, kernel_size);
            log_execution(layer_name, "Conv2D", std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count(), true);
        }
        else if (layer_type == "ReLU")
        {
            relu(input_data, output_data);
            log_execution(layer_name, "ReLU", std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count(), true);
        }
        else if (layer_type == "MaxPool")
        {
            int input_height = 4, input_width = 4, kernel_size = 2, stride = 2;
            maxpool(input_data, output_data, input_height, input_width, kernel_size, stride);
            log_execution(layer_name, "MaxPooling2D", std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count(), true);
        }
        else if (layer_type == "Softmax")
        {
            softmax(input_data, output_data);
            log_execution(layer_name, "Softmax", std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count(), true);
        }
        else if (layer_type == "Add")
        {
            std::string second_input_path = "../data/input/" + layer_name + "_input2.bin";
            std::vector<float> input_data2 = read_binary_file(second_input_path);

            if (input_data2.empty() || input_data.size() != input_data2.size())
            {
                log_execution(layer_name, "Add", 0.0, false);
                std::cerr << "ERROR: Add Layer requires two valid input tensors of the same size!" << std::endl;
                return 1;
            }

            Add addLayer;
            output_data = addLayer.forward(input_data, input_data2);
            log_execution(layer_name, "Add", std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count(), true);
        }
        else if (layer_type == "MatMul")
        {
            std::string weights_path = "../data/input/" + layer_name + "_weights.bin";
            std::string bias_path = "../data/input/" + layer_name + "_bias.bin";

            std::vector<float> weights = read_binary_file(weights_path);
            std::vector<float> bias = read_binary_file(bias_path);

            if (weights.empty() || bias.empty())
            {
                log_execution(layer_name, "MatMul", 0.0, false);
                std::cerr << "ERROR: MatMul requires valid weight & bias files!" << std::endl;
                return 1;
            }

            int input_size = input_data.size();
            int output_size = bias.size();

            MatMul matmulLayer;
            output_data = matmulLayer.forward(input_data, weights, bias, input_size, output_size);
            log_execution(layer_name, "Dense", std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count(), true);
        }
        else
        {
            std::cerr << "Unknown layer type: " << layer_type << std::endl;
            continue;
        }

        prev_output = output_data; // Pass the output to next layer

        // Save layer inputs and outputs
        save_layer_dump(layer_name, input_data, "input");
        save_layer_dump(layer_name, output_data, "output");

        std::cout << "Layer Execution Completed." << std::endl;
    }

    std::cout << "Model Execution Completed Successfully!" << std::endl;
    return 0;
}
