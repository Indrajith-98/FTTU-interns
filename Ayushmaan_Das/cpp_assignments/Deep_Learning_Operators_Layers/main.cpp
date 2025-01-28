#include <onnxruntime_cxx_api.h>
#include <iostream>
#include <vector>
#include <string>

void loadModel(const std::string &modelPath)
{
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "ONNXModelDump");
    Ort::SessionOptions sessionOptions;
    try
    {
        Ort::Session session(env, modelPath.c_str(), sessionOptions);
        Ort::ModelMetadata modelMetadata = session.GetModelMetadata();
        std::cout << "Model Version: " << modelMetadata.GetVersion() << std::endl;
    }

    catch (const std::exception &e)
    {
        std::cout << "Error loading model: " << e.what() << std::endl;
    }
}

int main()
{
    loadModel("../models/hypertuned_resnet34_fashion_mnist.onnx");
    return 0;
}