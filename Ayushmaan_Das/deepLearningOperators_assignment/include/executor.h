#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "onnx_model.h"
#include "operators.h"
#include <fstream>
#include <chrono>

class Executor
{
public:
    explicit Executor(ONNXModel &model) : model(model) {}
    void executeModel();

private:
    ONNXModel &model;
    void logExecution(const std::string &layerName, const std::string &function, double timeMs, bool success);
};

#endif
