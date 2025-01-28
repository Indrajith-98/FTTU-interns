#include "../include/prelu_test.h"
#include "../../utils/include/FileUtils.h"

void PReluTest :: checkPReluLayerOutput(const std::string& imagePath,const std::string& layerName,const std::vector<std::vector<std::vector<double>>>& feature_map)
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

