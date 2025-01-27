#include "../include/FileUtils.h"

std::vector<std::vector<std::vector<double>>> FileUtils::read_image_matrix(const std::string& file_path) {
    std::ifstream input_file(file_path);
    if (!input_file.is_open()) {
        throw std::runtime_error("Error: Unable to open file: " + file_path);
    }

    json image_json;
    input_file >> image_json;

    return image_json.get<std::vector<std::vector<std::vector<double>>>>();
}

void FileUtils::display_image_shape(const std::vector<std::vector<std::vector<double>>>& image_matrix) {
    size_t height = image_matrix.size();
    size_t width = image_matrix[0].size();
    size_t channels = image_matrix[0][0].size();

    std::cout << "Input Image shape: " << height << "x" << width << "x" << channels << std::endl;
}

json FileUtils::read_model_config(const std::string& file_path) {
    std::ifstream input_file(file_path);
    if (!input_file.is_open()) {
        throw std::runtime_error("Error: Unable to open file: " + file_path);
    }

    json model_json;
    input_file >> model_json;

    return model_json;
}

std::string FileUtils::extractFilename(const std::string& filePath) {
    size_t lastSlashPos = filePath.find_last_of('/');
    
    size_t lastDotPos = filePath.find_last_of('.');
    
    std::string filename = filePath.substr(lastSlashPos + 1, lastDotPos - lastSlashPos - 1);
    
    return filename;
}
