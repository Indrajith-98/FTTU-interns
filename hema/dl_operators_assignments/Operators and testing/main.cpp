#include <iostream>
#include <fstream>
#include <chrono> // For measuring time
#include "conv2d.h"
#include "dense.h"
#include "max_pooling.h"
#include "softmax.h"
#include "flatten.h"
#include "relu.h"
#include "utils.h"
#include "testing.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;


int main() {
    // Start measuring total execution time
    auto program_start = std::chrono::high_resolution_clock::now();

    // Read the JSON configuration file
    std::ifstream config_file("D:/Documents_personal/Multicoreware/assignments/assignment 2/Model_test/model_config.json");
    json config;
    config_file >> config;

    auto& conv1_config = config[0];
    int conv1_input_channels = conv1_config["config"]["input_channels"];
    int conv1_filters = conv1_config["config"]["filters"];
    int conv1_kernel_size = conv1_config["config"]["kernel_size"][0];

    Conv2D conv1(conv1_input_channels, conv1_filters, conv1_kernel_size);

    // Layer instances
    MaxPool2D maxpool1, maxpool2;
    ReLU relu;
    Flatten flatten;

    conv1.load_weights(
        read_weights_from_file(conv1_config["weights_files_path"][0]), 
        read_weights_from_file(conv1_config["weights_files_path"][1])
    );

    // Read input
    auto input = measure_time("Input Reading", [&]() {
        return read_image_from_file(conv1_config["input_file_path"], 32, 32);
    });

    // Conv1 Layer
    auto conv1_output = measure_time("Conv1 Forward Pass", [&]() {
        return conv1.forward(input);
    });
    auto relu1_output = measure_time("ReLU1 Activation", [&]() {
        return relu.forward(conv1_output);
    });
    print_3d_vector(relu1_output, "conv1.txt");

    // MaxPool1 Layer
    auto pooled1_output = measure_time("MaxPool1 Forward Pass", [&]() {
        return maxpool1.forward(relu1_output);
    });
    print_3d_vector(pooled1_output, "pool1.txt");

    // Conv2 Layer
    auto& conv2_config = config[2];
    int conv2_input_channels = conv2_config["config"]["input_channels"];
    int conv2_filters = conv2_config["config"]["filters"];
    int conv2_kernel_size = conv2_config["config"]["kernel_size"][0];

    Conv2D conv2(conv2_input_channels, conv2_filters, conv2_kernel_size);
    conv2.load_weights(
        read_weights_from_file(conv2_config["weights_files_path"][0]), 
        read_weights_from_file(conv2_config["weights_files_path"][1])
    );

    auto conv2_output = measure_time("Conv2 Forward Pass", [&]() {
        return conv2.forward(pooled1_output);
    });
    auto relu2_output = measure_time("ReLU2 Activation", [&]() {
        return relu.forward(conv2_output);
    });
    print_3d_vector(relu2_output, "conv2.txt");

    // MaxPool2 Layer
    auto pooled2_output = measure_time("MaxPool2 Forward Pass", [&]() {
        return maxpool2.forward(relu2_output);
    });
    print_3d_vector(pooled2_output, "pool2.txt");

    // Conv3 Layer
    auto& conv3_config = config[4];
    int conv3_input_channels = conv3_config["config"]["input_channels"];
    int conv3_filters = conv3_config["config"]["filters"];
    int conv3_kernel_size = conv3_config["config"]["kernel_size"][0];

    Conv2D conv3(conv3_input_channels, conv3_filters, conv3_kernel_size);
    conv3.load_weights(
        read_weights_from_file(conv3_config["weights_files_path"][0]), 
        read_weights_from_file(conv3_config["weights_files_path"][1])
    );

    auto conv3_output = measure_time("Conv3 Forward Pass", [&]() {
        return conv3.forward(pooled2_output);
    });
    auto relu3_output = measure_time("ReLU3 Activation", [&]() {
        return relu.forward(conv3_output);
    });
    print_3d_vector(relu3_output, "conv3.txt");

    // Flatten Layer
    auto flattened_output = measure_time("Flattening", [&]() {
        return flatten.forward(relu3_output);
    });
    print_1d_vector(flattened_output, "flatten.txt");

    // Fully Connected Layers
    auto& fc1_config = config[6];
    int fc1_input_units = fc1_config["config"]["input_units"];
    int fc1_units = fc1_config["config"]["units"];

    Dense fc1(fc1_input_units, fc1_units);
    fc1.load_weights(
        read_weights_from_file(fc1_config["weights_files_path"][0]), 
        read_weights_from_file(fc1_config["weights_files_path"][1])
    );

    auto fc1_output = measure_time("Dense1 Forward Pass", [&]() {
        return fc1.forward(flattened_output);
    });
    auto relu_fc1_output = measure_time("ReLU FC1 Activation", [&]() {
        return relu.forward(fc1_output);
    });
    print_1d_vector(relu_fc1_output, "dense1.txt");

    auto& fc2_config = config[7];
    int fc2_input_units = fc2_config["config"]["input_units"];
    int fc2_units = fc2_config["config"]["units"];

    Dense fc2(fc2_input_units, fc2_units);
    fc2.load_weights(
        read_weights_from_file(fc2_config["weights_files_path"][0]), 
        read_weights_from_file(fc2_config["weights_files_path"][1])
    );

    auto fc2_output = measure_time("Dense2 Forward Pass", [&]() {
        return fc2.forward(relu_fc1_output);
    });

    // Softmax Layer
    auto final_output = measure_time("Softmax Activation", [&]() {
        return Softmax::forward(fc2_output);
    });
    print_1d_vector(final_output, "dense2.txt");

    // End of program timing
    auto program_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total_elapsed = program_end - program_start;
    std::cout << "Total Program Execution Time: " << total_elapsed.count() << " seconds\n";



    std::cout<<"Testing the model\n";
    auto test_start = std::chrono::high_resolution_clock::now();

    std::string output_file1 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/report/conv.txt";
    std::string expected_file1 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/data/output/conv2d_output.txt";
    std::string output_file2 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/report/pooling.txt";
    std::string expected_file2 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/data/output/max_pooling2d_output.txt";
    std::string output_file3 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/report/conv1.txt";
    std::string expected_file3 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/data/output/conv2d_1_output.txt";
    std::string output_file4 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/report/pooling1.txt";
    std::string expected_file4 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/data/output/max_pooling2d_1_output.txt";
    std::string output_file5 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/report/conv2.txt";
    std::string expected_file5 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/data/output/conv2d_2_output.txt";
    std::string output_file6 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/report/flatten.txt";
    std::string expected_file6 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/data/output/flatten_output.txt";
    std::string output_file7 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/report/dense.txt";
    std::string expected_file7 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/data/output/dense_output.txt";
    std::string output_file8 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/report/dense1.txt";
    std::string expected_file8 = "D:/Documents_personal/Multicoreware/assignments/assignment 2/cpp cifar-10/data/output/dense_1_output.txt";

    // Compare the files
    unit_test("conv1",output_file1, expected_file1);
    unit_test("pool1",output_file2, expected_file2);
    unit_test("conv2",output_file3, expected_file3);
    unit_test("pool2",output_file4, expected_file4);
    unit_test("conv3",output_file5, expected_file5);
    unit_test("flatten",output_file6, expected_file6);
    unit_test("dense1",output_file7, expected_file7);
    unit_test("dense2",output_file8, expected_file8);
    model_test(output_file8, expected_file8);
    
    auto test_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> testing_time = test_end - test_start;
    std::cout << "Total Testing Time: " << testing_time.count() << " seconds\n";

     // Total program execution
    std::chrono::duration<double> total_program_time = test_end - program_start;
    std::cout << "Total Program Execution Time (Model + Testing): " << total_program_time.count() << " seconds\n";

    return 0;
}
