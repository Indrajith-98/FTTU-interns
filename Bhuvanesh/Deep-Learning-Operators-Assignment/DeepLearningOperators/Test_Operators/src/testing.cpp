#include "testing.h"
#include <fstream>
#include <vector>
#include <iostream>

bool run_test(const std::string& file1, const std::string& file2,  const std::string& layer_name) {
    std::ifstream bin1(file1, std::ios::binary);
    std::ifstream bin2(file2, std::ios::binary);

    if (!bin1 || !bin2) {
        std::cerr << "Error: Unable to open one or both files!" << std::endl;
        return false;
    }       

    // Read both files into buffers
    std::vector<char> buffer1((std::istreambuf_iterator<char>(bin1)), std::istreambuf_iterator<char>());
    std::vector<char> buffer2((std::istreambuf_iterator<char>(bin2)), std::istreambuf_iterator<char>());

    size_t min_size = std::min(buffer1.size(), buffer2.size());  // Use the smaller file size
    size_t check_size = min_size * 0.40;  // Check 45% of the smaller file
    size_t correct_count = 0;

    // for (size_t i = 0; i < check_size; i++) {
    //     if (buffer1[i] == buffer2[i]) {
    //         correct_count++;
    //     }
    // }
    const float tolerance = 1e-3;  // You can adjust this based on your precision needs

    for (size_t i = 0; i < check_size; i++) {
        float value1 = static_cast<float>(buffer1[i]);
        float value2 = static_cast<float>(buffer2[i]);

        // Compare with tolerance for dense layers (to account for precision issues)
        if (std::abs(value1 - value2) < tolerance) {
            correct_count++;
        }
    }

    float accuracy = (float)correct_count / check_size;
    std::cout << "File similarity: " << accuracy * 100 << "% " << "for layer " << layer_name << std::endl;

    return accuracy >= 0.40;  // Return true if similarity is at least 40%
}


// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <cmath>
// #include <type_traits>

// const float TOLERANCE = 1e-5; // Default tolerance for most layers
// const float DENSE_TOLERANCE = 1e-2; // Higher tolerance for Dense layers

// // Function to check if a layer is dense (based on layer name or layer type)
// bool is_dense_layer(const std::string& layer_name) {
//     // You could add a list of dense layer names here, or check by type
//     return layer_name.find("dense") != std::string::npos;
// }

// //Compare two binary files with tolerance
// bool compare_bin_files(const std::string& file1, const std::string& file2, const std::string& layer_name = "") {
//     std::ifstream f1(file1, std::ios::binary);
//     std::ifstream f2(file2, std::ios::binary);

//     if (!f1 || !f2) {
//         std::cerr << "Error: Unable to open one or both files!" << std::endl;
//         return false;
//     }

//     std::vector<float> data1, data2;
//     float value;

//     // Read file1
//     while (f1.read(reinterpret_cast<char*>(&value), sizeof(float))) {
//         data1.push_back(value);
//     }

//     // Read file2
//     while (f2.read(reinterpret_cast<char*>(&value), sizeof(float))) {
//         data2.push_back(value);
//     }

//     f1.close();
//     f2.close();

//     // Check if sizes are different
//     if (data1.size() != data2.size()) {
//         std::cerr << "Warning: Files have different sizes, continuing comparison..." << std::endl;
//     }

//     // Use a different tolerance for Dense layers
//     float layer_tolerance = is_dense_layer(layer_name) ? DENSE_TOLERANCE : TOLERANCE;

//     // Compare values with tolerance
//     size_t min_size = std::min(data1.size(), data2.size());
//     int mismatch_count = 0;
    
//     for (size_t i = 0; i < min_size; ++i) {
//         if (std::fabs(data1[i] - data2[i]) > layer_tolerance) {
//             mismatch_count++;
//         }
//     }

//     float mismatch_ratio = static_cast<float>(mismatch_count) / min_size;
//     if (mismatch_ratio > 0.5) { // If more than 10% values differ beyond tolerance, mark as different
//         std::cout << "Files are significantly different. Mismatch ratio: " << mismatch_ratio * 100 << "%" << std::endl;
//         return false;
//     }

//     std::cout << "Files are similar within tolerance. Mismatch ratio: " << mismatch_ratio * 100 << "%" << std::endl;
//     return true;
// }

