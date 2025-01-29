#include <onnxruntime_cxx_api.h>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// Function to dump input/output layers and weights/biases
void dumpModelLayers(Ort::Session &session, Ort::ModelMetadata &modelMetadata)
{
    size_t numInputs = session.GetInputCount();
    size_t numOutputs = session.GetOutputCount();

    // Input layers details
    std::cout << "Number of Inputs: " << numInputs << std::endl;
    for (size_t i = 0; i < numInputs; ++i)
    {
        Ort::TypeInfo inputTypeInfo = session.GetInputTypeInfo(i);
        auto inputShape = inputTypeInfo.GetTensorTypeAndShapeInfo().GetShape();
        std::cout << "Input " << i << " Shape: ";
        for (auto dim : inputShape)
        {
            std::cout << dim << " ";
        }
        std::cout << std::endl;

        // Optionally, dump the input tensor type
        std::string inputType = inputTypeInfo.GetTensorTypeAndShapeInfo().GetElementType() == ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT ? "FLOAT" : "OTHER";
        std::cout << "Input " << i << " Type: " << inputType << std::endl;
    }

    // Output layers details
    std::cout << "Number of Outputs: " << numOutputs << std::endl;
    for (size_t i = 0; i < numOutputs; ++i)
    {
        Ort::TypeInfo outputTypeInfo = session.GetOutputTypeInfo(i);
        auto outputShape = outputTypeInfo.GetTensorTypeAndShapeInfo().GetShape();
        std::cout << "Output " << i << " Shape: ";
        for (auto dim : outputShape)
        {
            std::cout << dim << " ";
        }
        std::cout << std::endl;

        std::string outputType = outputTypeInfo.GetTensorTypeAndShapeInfo().GetElementType() == ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT ? "FLOAT" : "OTHER";
        std::cout << "Output " << i << " Type: " << outputType << std::endl;
    }
}

int main()
{
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "ONNXModelDump");
    Ort::SessionOptions sessionOptions;
    try
    {
        Ort::Session session(env, "../models/hypertuned_resnet34_fashion_mnist.onnx", sessionOptions);
        Ort::ModelMetadata modelMetadata = session.GetModelMetadata();
        std::cout << "Model Version: " << modelMetadata.GetVersion() << std::endl;

        Ort::AllocatorWithDefaultOptions allocator;
        auto graphNameAllocated = modelMetadata.GetGraphNameAllocated(allocator);
        std::string graphName = graphNameAllocated.get();
        std::cout << "Graph Name: " << graphName << std::endl;

        dumpModelLayers(session, modelMetadata);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error loading model: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
