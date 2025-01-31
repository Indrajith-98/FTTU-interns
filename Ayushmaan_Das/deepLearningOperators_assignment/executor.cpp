#include "executor.h"

void Executor::executeModel()
{
    std::ofstream logFile("logs/execution_log.txt", std::ios::out);

    for (const auto &node : model.nodes)
    {
        auto start = std::chrono::high_resolution_clock::now();
        bool success = false;

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
            std::vector<int> newShape;
            for (float val : model.tensors[node.inputs[1]].data)
            {
                newShape.push_back(static_cast<int>(val));
            }

            success = executeReshape(model.tensors[node.inputs[0]], model.tensors[node.outputs[0]], newShape);
        }

        else if (node.opType == "MaxPool")
        {
            int kernelSize = model.tensors[node.inputs[1]].data[0];
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
