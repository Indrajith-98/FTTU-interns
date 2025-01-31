#include "operators.h"
#include <algorithm>
#include <numeric>

bool executeAdd(const Tensor &input1, const Tensor &input2, Tensor &output)
{
    std::cout << "Executing Add: Input1 Shape: " << input1.shape.size()
              << ", Input2 Shape: " << input2.shape.size() << std::endl;

    if (input1.data.empty() || input2.data.empty())
    {
        std::cerr << "Error: One of the input tensors is empty!" << std::endl;
        return false;
    }

    if (input1.shape != input2.shape)
    {
        std::cerr << "Shape mismatch in Add operation: ";
        for (int s : input1.shape)
            std::cerr << s << " ";
        std::cerr << " vs ";
        for (int s : input2.shape)
            std::cerr << s << " ";
        std::cerr << std::endl;
        return false;
    }

    output.shape = input1.shape;
    output.data.resize(input1.data.size());

    for (size_t i = 0; i < input1.data.size(); ++i)
    {
        output.data[i] = input1.data[i] + input2.data[i];
    }

    return true;
}

bool executeMul(const Tensor &input1, const Tensor &input2, Tensor &output)
{
    std::cout << "Executing Mul: Input1 Shape: " << input1.shape.size()
              << ", Input2 Shape: " << input2.shape.size() << std::endl;

    if (input1.data.empty() || input2.data.empty())
    {
        std::cerr << "Error: One of the input tensors is empty!" << std::endl;
        return false;
    }

    if (input1.shape != input2.shape)
    {
        std::cerr << "Shape mismatch in Mul operation: ";
        for (int s : input1.shape)
            std::cerr << s << " ";
        std::cerr << " vs ";
        for (int s : input2.shape)
            std::cerr << s << " ";
        std::cerr << std::endl;
        return false;
    }

    output.shape = input1.shape;
    output.data.resize(input1.data.size());

    for (size_t i = 0; i < input1.data.size(); ++i)
    {
        output.data[i] = input1.data[i] * input2.data[i];
    }

    return true;
}

bool executeRelu(const Tensor &input, Tensor &output)
{
    output.shape = input.shape;
    output.data.resize(input.data.size());

    for (size_t i = 0; i < input.data.size(); ++i)
    {
        output.data[i] = std::max(0.0f, input.data[i]);
    }

    return true;
}

bool executeMatMul(const Tensor &input1, const Tensor &input2, Tensor &output)
{
    if (input1.shape.size() != 2 || input2.shape.size() != 2 || input1.shape[1] != input2.shape[0])
    {
        std::cerr << "Shape mismatch in MatMul operation\n";
        return false;
    }

    output.shape = {input1.shape[0], input2.shape[1]};
    output.data.resize(output.shape[0] * output.shape[1], 0);

    for (size_t i = 0; i < output.shape[0]; ++i)
    {
        for (size_t j = 0; j < output.shape[1]; ++j)
        {
            for (size_t k = 0; k < input1.shape[1]; ++k)
            {
                output.data[i * output.shape[1] + j] += input1.data[i * input1.shape[1] + k] * input2.data[k * input2.shape[1] + j];
            }
        }
    }
    return true;
}

bool executeSoftmax(const Tensor &input, Tensor &output)
{
    output.shape = input.shape;
    output.data.resize(input.data.size());

    for (size_t i = 0; i < input.shape[0]; ++i)
    {
        float sumExp = 0;
        for (size_t j = 0; j < input.shape[1]; ++j)
        {
            output.data[i * input.shape[1] + j] = std::exp(input.data[i * input.shape[1] + j]);
            sumExp += output.data[i * input.shape[1] + j];
        }
        for (size_t j = 0; j < input.shape[1]; ++j)
        {
            output.data[i * input.shape[1] + j] /= sumExp;
        }
    }
    return true;
}

bool executeReshape(const Tensor &input, Tensor &output, const std::vector<int> &newShape)
{
    std::cout << "Executing Reshape: New Shape: ";
    for (int s : newShape)
        std::cout << s << " ";
    std::cout << std::endl;

    int totalElements = 1;
    for (int dim : newShape)
    {
        if (dim > 0)
            totalElements *= dim;
    }

    if (input.data.size() != totalElements)
    {
        std::cerr << "Error: Reshape mismatch! Input size: " << input.data.size()
                  << ", Expected: " << totalElements << std::endl;
        return false;
    }

    output.shape = newShape;
    output.data = input.data;

    std::cout << "Reshaped Output Shape: ";
    for (int s : output.shape)
        std::cout << s << " ";
    std::cout << std::endl;
    return true;
}

bool executeMaxPool(const Tensor &input, Tensor &output, int kernelSize)
{
    if (input.shape.size() != 2)
    {
        std::cerr << "Invalid shape for MaxPool\n";
        return false;
    }

    int pooledHeight = input.shape[0] / kernelSize;
    int pooledWidth = input.shape[1] / kernelSize;
    output.shape = {pooledHeight, pooledWidth};
    output.data.resize(pooledHeight * pooledWidth);

    for (int i = 0; i < pooledHeight; ++i)
    {
        for (int j = 0; j < pooledWidth; ++j)
        {
            float maxVal = -std::numeric_limits<float>::infinity();
            for (int ki = 0; ki < kernelSize; ++ki)
            {
                for (int kj = 0; kj < kernelSize; ++kj)
                {
                    maxVal = std::max(maxVal, input.data[(i * kernelSize + ki) * input.shape[1] + (j * kernelSize + kj)]);
                }
            }
            output.data[i * pooledWidth + j] = maxVal;
        }
    }
    return true;
}

bool executeGlobalAveragePool(const Tensor &input, Tensor &output)
{
    float sum = std::accumulate(input.data.begin(), input.data.end(), 0.0f);
    float avg = sum / input.data.size();
    output.shape = {1};
    output.data = {avg};
    return true;
}
