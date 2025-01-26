#include "../include/conv_test.h"
#include "../../utils/include/FileUtils.h"

void ConvTest :: checkOutputShape(const std::vector<int>& expected_output_shape,int calculated_height, int calculated_width, int calculated_depth)
{

    assert(calculated_height == expected_output_shape[1] && 
           "Calculated output height does not match expected height.");
    assert(calculated_width == expected_output_shape[2] && 
           "Calculated output width does not match expected width.");
    assert(calculated_depth == expected_output_shape[3] && 
           "Calculated output depth does not match expected depth.");
}

void ConvTest :: checkConvLayerOutput(const std::string& imagePath,const std::string& layerName,const std::vector<std::vector<std::vector<double>>>& feature_map)
{
    std::string filename = FileUtils :: extractFilename(imagePath);
    std::string modelFile = "../data/reference/model_result_for_" + filename + ".json";

    std::ifstream file(modelFile);
    if (!file.is_open()) {
        std::cerr << "Could not open the file " << modelFile << std::endl;
        return;
    }

    nlohmann::json jsonData;
    file >> jsonData;
    for (const auto& element : jsonData) {
        if (element.contains("layer_outputs")) {
            auto actualOutput = element["layer_outputs"][layerName];
            for (int i = 0; i < actualOutput.size(); ++i) {
                for (int j = 0; j < actualOutput[i].size(); ++j) {
                    for (int k = 0; k < actualOutput[i][j].size(); ++k) {\
                        double val = actualOutput[0][i][j][k];
                        assert(fabs(val - feature_map[i][j][k]) < 1e-4 && "Output value mismatch");
                    }
                }
            }
        }
    }
}

