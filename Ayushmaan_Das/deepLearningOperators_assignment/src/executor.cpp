#include "executor.h"

void Executor::executeModel()
{
    std::ofstream logFile("logs/execution_log.txt", std::ios::out);

    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "Available Tensors in Model:" << std::endl;
    for (const auto &tensor : model.tensors)
    {
        std::cout << " - " << tensor.first << " (shape: ";
        for (int dim : tensor.second.shape)
            std::cout << dim << " ";
        std::cout << ")" << std::endl;
    }
    std::cout << "\n--------------------------------------------" << std::endl;

    for (const auto &node : model.nodes)
    {
        auto start = std::chrono::high_resolution_clock::now();
        bool success = false;


        std::cout << "Executing Node: " << node.name << " | OpType: " << node.opType << std::endl;
        for (const auto &input : node.inputs)
        {
            if (model.tensors.find(input) == model.tensors.end())
            {
                std::cerr << "Error: Input tensor " << input << " not found for node " << node.name << std::endl;
                continue;
            }
            const Tensor &inputTensor = model.tensors[input];
            std::cout << "Input Tensor: " << input << " | Shape: ";
            for (int dim : inputTensor.shape)
                std::cout << dim << " ";
            std::cout << std::endl; 
        }

        for (const auto &output : node.outputs)
        {
            if (model.tensors.find(output) == model.tensors.end())
            {
                model.tensors[output] = Tensor(); // Initialize an empty tensor
                std::cout << "Initialized output tensor: " << output << std::endl;
            }
        }

        if (node.opType == "Add")
        {
            success = executeAdd(model.tensors[node.inputs[0]], model.tensors[node.inputs[1]], model.tensors[node.outputs[0]]);
        }
        else if (node.opType == "Mul")
        {
            success = executeMul(model.tensors[node.inputs[0]], model.tensors[node.inputs[1]], model.tensors[node.outputs[0]]);
        }
        else if (node.opType == "Relu")
        {
            success = executeRelu(model.tensors[node.inputs[0]], model.tensors[node.outputs[0]]);
        }
        else if (node.opType == "MatMul")
        {
            success = executeMatMul(model.tensors[node.inputs[0]], model.tensors[node.inputs[1]], model.tensors[node.outputs[0]]);
        }
        else if (node.opType == "Softmax")
        {
            success = executeSoftmax(model.tensors[node.inputs[0]], model.tensors[node.outputs[0]]);
        }
        else if (node.opType == "Reshape")
        {
            if (model.tensors.find(node.inputs[1]) == model.tensors.end())
            {
                std::cerr << "Error: Shape tensor not found for Reshape operation!" << std::endl;
                continue;
            }

            std::vector<int> newShape;
            for (float val : model.tensors[node.inputs[1]].data)
            {
                int dim = static_cast<int>(val);
                if (dim <= 0 && dim != -1) 
                {
                    std::cerr << "Error: Invalid reshape dimension: " << dim << std::endl;
                    continue;
                }
                newShape.push_back(dim);
            }

            if (newShape.empty())
            {
                std::cerr << "Error: Reshape operation received an empty shape tensor!" << std::endl;
                continue;
            }

            success = executeReshape(model.tensors[node.inputs[0]], model.tensors[node.outputs[0]], newShape);
        }
        else if (node.opType == "MaxPool")
        {
            int kernelSize = static_cast<int>(model.tensors[node.inputs[1]].data[0]);
            success = executeMaxPool(model.tensors[node.inputs[0]], model.tensors[node.outputs[0]], kernelSize);
        }
        else if (node.opType == "GlobalAveragePool")
        {
            success = executeGlobalAveragePool(model.tensors[node.inputs[0]], model.tensors[node.outputs[0]]);
        }
        else
        {
            logFile << "Unsupported opType: " << node.opType << "\n";
            continue;
        }

        auto end = std::chrono::high_resolution_clock::now();
        double timeMs = std::chrono::duration<double, std::milli>(end - start).count();
        logExecution(node.name, node.opType, timeMs, success);
    }
    logFile.close();
}

void Executor::logExecution(const std::string &layerName, const std::string &function, double timeMs, bool success)
{
    std::ofstream logFile("../logs/execution_log.txt", std::ios::app);
    logFile << "Layer: " << layerName << " | Function: " << function
            << " | Time: " << timeMs << "ms | Status: " << (success ? "PASS" : "FAIL") << "\n";
    logFile.close();
}
