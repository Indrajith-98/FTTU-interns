#include <iostream>
#include "onnx_model.h"
#include "executor.h"

int main()
{
    std::cout << "Starting ONNX Model Execution..." << std::endl;

    // Load the model
    ONNXModel model;
    std::string modelPath = "../configs/model_config.json";

    if (!model.loadModel(modelPath))
    {
        std::cerr << "Failed to load model from: " << modelPath << std::endl;
        return 1;
    }

    std::cout << "Model loaded successfully!" << std::endl;

    // Execute the model
    Executor executor(model);
    std::cout << "Executing model..." << std::endl;
    executor.executeModel();

    std::cout << "Execution completed!" << std::endl;
    return 0;
}
