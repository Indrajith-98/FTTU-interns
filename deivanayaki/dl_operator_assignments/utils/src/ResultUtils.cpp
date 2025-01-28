#include "../include/ResultUtils.h"
#include "../include/IntermediateResultUtils.h"
#include "../include/FileUtils.h"
#include "../include/LogUtils.h"

void ResultUtils :: appendPrediction(const std::string& imagePath, const std::vector<double>& probabilities, const std::map<std::string,std::vector<std::vector<std::vector<double>>>>& layer3d_outputs,const std::map<std::string,std::vector<double>>& layer1d_outputs) {

    std::vector<std::string> class_labels = {
        "airplane", "automobile", "bird", "cat", "deer", 
        "dog", "frog", "horse", "ship", "truck"
    };
    std::string outputFile = "../Reports/predictions.json";

    std::cout << std::setprecision(6) << std::scientific;
    int maxIndex = 0;
    double maxValue = probabilities[0];
    for (int i = 0; i < probabilities.size(); i++) {
        if (probabilities[i] > maxValue) {
            maxValue = probabilities[i];
            maxIndex = i;
        }
        std::cout<<class_labels[i]<<"\t : "<< probabilities[i] <<std::endl;
    }
    std::cout << "Predicted Class: " << class_labels[maxIndex] << std::endl;

    IntermediateResultUtils :: storeIntermediateResults(imagePath,probabilities,maxIndex,class_labels[maxIndex],layer3d_outputs,layer1d_outputs);

    json result;
    result["input_image_path"] = imagePath;
    result["class_probabilities"] = probabilities;
    result["predicted_index"] = maxIndex;
    result["predicted_label"] = class_labels[maxIndex];

    ResultUtils :: modelTest(imagePath,class_labels[maxIndex]);

    std::ifstream inputFile(outputFile);
    json allResults;

    if (inputFile.is_open()) {
        inputFile >> allResults;
        inputFile.close();
    } else {
        allResults = json::array();
    }

    bool imagePathExists = false;
    for (const auto& entry : allResults) {
        if (entry["input_image_path"] == imagePath) {
            imagePathExists = true;
            break;
        }
    }

    if (!imagePathExists) {
        allResults.push_back(result);
        std::ofstream outputFileStream(outputFile);
        if (outputFileStream.is_open()) {
            outputFileStream << allResults.dump(4);  
            outputFileStream.close();
        } else {
            std::cerr << "Error: Unable to open " << outputFile << " for writing!" << std::endl;
        }
    } 
}

void ResultUtils :: modelTest(const std::string& imagePath, const std::string& predicted)
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
    unitTestLogExecution("Model Test : ");
    for (const auto& element : jsonData) {
        if(element["predicted_label"]==predicted && predicted!=element["actual_class_label"])
        {
            unitTestLogExecution("Model works well but failed to predict correctly");
        }
        else if(element["predicted_label"]==predicted)
        {
            unitTestLogExecution("Model works well and predicted the result correctly");
        }
        else
        {
            unitTestLogExecution("Model does not works correctly");
        }
    }
}