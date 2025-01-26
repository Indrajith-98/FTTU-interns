#include "../include/IntermediateResultUtils.h"
#include "../include/FileUtils.h"

void IntermediateResultUtils::storeIntermediateResults(
    const std::string& image_path, 
    const std::vector<double>& class_probabilities, 
    int predicted_index, 
    const std::string& predicted_label,
    const std::map<std::string,std::vector<std::vector<std::vector<double>>>>& layer3d_outputs,const std::map<std::string,std::vector<double>>& layer1d_outputs
    ) {
    json result;

    result["input_image_path"] = image_path;
    result["class_probabilities"] = class_probabilities;
    result["predicted_index"] = predicted_index;
    result["predicted_label"] = predicted_label;
    
    for (const auto& [key, value] : layer1d_outputs) {
        result["layer_outputs"][key] = value; 
    }

    for (const auto& [key, value] : layer3d_outputs) {
        result["layer_outputs"][key] = value; 
    }

    std::string filename = FileUtils :: extractFilename(image_path);
    std::string outputFile = "../data/output/intermediate_result_for_" + filename + ".json";
    
    std::ifstream fileCheck(outputFile);
    if (fileCheck.good()) {
        std::cout << "File " << outputFile << " already exists. Skipping file creation." << std::endl;
    } else {
        std::ofstream outputFileStream(outputFile);
        if (outputFileStream.is_open()) {
            outputFileStream << result.dump(4);  // Pretty print with an indentation of 4 spaces
            outputFileStream.close();
        } else {
            std::cerr << "Failed to open " << outputFile << " for writing." << std::endl;
        }
    }   
}
