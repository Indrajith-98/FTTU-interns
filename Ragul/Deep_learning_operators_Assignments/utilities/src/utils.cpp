#include "utils.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <iomanip>
#include <filesystem>


// Template function definition for readBinaryFile
template<typename T>
std::vector<T> readBinaryFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file)
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (size % sizeof(T) != 0)
    {
        throw std::runtime_error("File size is not a multiple of data type size.");
    }

    std::vector<T> buffer(size / sizeof(T));
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
    {
        throw std::runtime_error("Error reading file: " + filename);
    }

    return buffer;
}

// Function definition for load_binary_file
std::vector<float> load_binary_file(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        exit(1);
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<float> data(size / sizeof(float));
    file.read(reinterpret_cast<char*>(data.data()), size);
    file.close();

    return data;
}


// #include "utils.h"
// #include <fstream>
// #include <iostream>
// #include <filesystem>
// #include <iomanip>

void store_data_to_file(const std::vector<float>& output,
                        const std::array<int, 4>& output_shape,
                        const std::string& layer_name,
                        const std::string& folder_path) {
    // Ensure the directory exists or create it
    try {
        if (!std::filesystem::exists(folder_path)) {
            if (!std::filesystem::create_directories(folder_path)) {
                std::cerr << "Error: Could not create directory at " << folder_path << std::endl;
                return;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: Exception while creating directory - " << e.what() << std::endl;
        return;
    }

    // Construct the full file path
    std::string file_name = folder_path + "/" + layer_name + "_output.txt";

    // Create and open the file
    std::ofstream outfile(file_name, std::ios::out | std::ios::trunc);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open or create file at " << file_name << std::endl;
        return;
    }

    // // Write the output to the file
    // outfile << "Layer: " << layer_name << "\n";

    // // Write output shape
    // outfile << "Output Shape: [";
    // for (size_t i = 0; i < output_shape.size(); ++i) {
    //     outfile << output_shape[i];
    //     if (i != output_shape.size() - 1) {
    //         outfile << ", ";
    //     }
    // }
    
    // outfile << "]\n\n";





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
                        outfile <<output[index]<< " ";
                        // std::cout << output[index] << " ";  // Print the value for the first channel
                    }
                     outfile << "\n";
                      // New line after each row
                }




    // Write output vector
    // outfile << "Output Data:\n";
    // for (const float& val : output) {
    //     outfile << val << " ";
    // }
    // outfile << "\n";

    // Close the file
    outfile.close();

    // Confirmation
    std::cout << "File created and data successfully written to: " << file_name << std::endl;
}


// Explicit template instantiation for readBinaryFile
template std::vector<float> readBinaryFile<float>(const std::string& filename);
template std::vector<int> readBinaryFile<int>(const std::string& filename);
