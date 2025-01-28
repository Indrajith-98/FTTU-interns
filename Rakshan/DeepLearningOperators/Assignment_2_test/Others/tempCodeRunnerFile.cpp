#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm> // For std::max

// Function to read binary data from a file
template <typename T>
void readBinaryFile(const std::string &filePath, std::vector<T> &data)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open file " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }
    file.seekg(0, std::ios::end);
    size_t size = file.tellg() / sizeof(T);
    file.seekg(0, std::ios::beg);
    data.resize(size);
    file.read(reinterpret_cast<char *>(data.data()), size * sizeof(T));
    file.close();
}

// Perform convolution
void convolve(const std::vector<float> &input, const std::vector<float> &kernel,
              const std::vector<float> &bias, std::vector<float> &output,
              int inputWidth, int inputHeight, int inputChannels, int outputChannels,
              int kernelSize, int stride, const std::string &padding)
{
    int pad = (padding == "same") ? kernelSize / 2 : 0;

    int outputWidth = inputWidth;
    int outputHeight = inputHeight;

    output.resize(outputWidth * outputHeight * outputChannels);

    for (int oc = 0; oc < outputChannels; ++oc)
    {
        for (int oh = 0; oh < outputHeight; ++oh)
        {
            for (int ow = 0; ow < outputWidth; ++ow)
            {
                float sum = bias[oc];
                for (int ic = 0; ic < inputChannels; ++ic)
                {
                    for (int kh = 0; kh < kernelSize; ++kh)
                    {
                        for (int kw = 0; kw < kernelSize; ++kw)
                        {
                            int ih = oh * stride + kh - pad;
                            int iw = ow * stride + kw - pad;
                            if (ih >= 0 && ih < inputHeight && iw >= 0 && iw < inputWidth)
                            {
                                int inputIdx = (ic * inputHeight + ih) * inputWidth + iw;
                                int kernelIdx = ((oc * inputChannels + ic) * kernelSize + kh) * kernelSize + kw;
                                sum += input[inputIdx] * kernel[kernelIdx];
                            }
                        }
                    }
                }
                int outputIdx = (oc * outputHeight + oh) * outputWidth + ow;
                output[outputIdx] = sum;
            }
        }
    }
}

// Apply ReLU activation function
void applyReLU(std::vector<float> &data)
{
    for (float &value : data)
    {
        value = std::max(0.0f, value);
    }
}

void dense(const std::vector<float> &input, const std::vector<float> &weights, const std::vector<float> &biases,
           std::vector<float> &output, int inputSize, int outputSize)
{
    output.resize(outputSize, 0.0f);
    for (int o = 0; o < outputSize; ++o)
    {
        for (int i = 0; i < inputSize; ++i)
        {
            output[o] += input[i] * weights[o * inputSize + i];
        }
        output[o] += biases[o];
    }
}

// Perform MaxPooling
void maxPooling(const std::vector<float> &input, std::vector<float> &output,
                int inputWidth, int inputHeight, int channels, int poolSize, int stride)
{
    int outputWidth = inputWidth / stride;
    int outputHeight = inputHeight / stride;

    output.resize(outputWidth * outputHeight * channels);

    for (int c = 0; c < channels; ++c)
    {
        for (int oh = 0; oh < outputHeight; ++oh)
        {
            for (int ow = 0; ow < outputWidth; ++ow)
            {
                float maxValue = -std::numeric_limits<float>::infinity();
                for (int ph = 0; ph < poolSize; ++ph)
                {
                    for (int pw = 0; pw < poolSize; ++pw)
                    {
                        int ih = oh * stride + ph;
                        int iw = ow * stride + pw;
                        if (ih < inputHeight && iw < inputWidth)
                        {
                            int inputIdx = (c * inputHeight + ih) * inputWidth + iw;
                            maxValue = std::max(maxValue, input[inputIdx]);
                        }
                    }
                }
                int outputIdx = (c * outputHeight + oh) * outputWidth + ow;
                output[outputIdx] = maxValue;
            }
        }
    }
}
void denseLayerWithSoftmax(const std::vector<float> &input, const std::vector<float> &weights,
                           const std::vector<float> &biases, std::vector<float> &output,
                           int inputSize, int outputSize)
{
    // Initialize the output vector
    output.resize(outputSize, 0.0f);

    // Perform the dense operation (matrix multiplication and bias addition)
    for (int o = 0; o < outputSize; ++o)
    {
        for (int i = 0; i < inputSize; ++i)
        {
            output[o] += input[i] * weights[o * inputSize + i];
        }
        output[o] += biases[o];
    }

    // Apply softmax activation
    float maxVal = *std::max_element(output.begin(), output.end());
    float sumExp = 0.0f;

    for (float &value : output)
    {
        value = std::exp(value - maxVal); // Subtract maxVal for numerical stability
        sumExp += value;
    }

    for (float &value : output)
    {
        value /= sumExp;
    }
}

int main()
{
    // File paths for the first convolution layer
    std::string inputPath = "D:/MCW/Assignment-2/resized_image_binary.bin";
    std::string kernelPath1 = "D:/MCW/Assignment-1/data/weights/conv2d_kernel.bin";
    std::string biasPath1 = "D:/MCW/Assignment-1/data/weights/conv2d_bias.bin";

    // File paths for the second convolution layer
    std::string kernelPath2 = "D:/MCW/Assignment-1/data/weights/conv2d_1_kernel.bin";
    std::string biasPath2 = "D:/MCW/Assignment-1/data/weights/conv2d_1_bias.bin";

    // File paths for the third convolution layer
    std::string kernelPath3 = "D:/MCW/Assignment-1/data/weights/conv2d_2_kernel.bin";
    std::string biasPath3 = "D:/MCW/Assignment-1/data/weights/conv2d_2_bias.bin";

    // First layer dimensions
    const int inputWidth = 32;
    const int inputHeight = 32;
    const int inputChannels = 3;
    const int outputChannels1 = 64;
    const int kernelSize = 3;
    const int stride = 1;
    const std::string padding = "same";

    // Second layer dimensions
    const int outputChannels2 = 128;

    // Third layer dimensions
    const int outputChannels3 = 128;

    // Read input, kernel, and bias for the first layer
    std::vector<float> input, kernel1, bias1, convOutput1, maxPoolOutput1;
    readBinaryFile(inputPath, input);
    readBinaryFile(kernelPath1, kernel1);
    readBinaryFile(biasPath1, bias1);

    // Perform first convolution
    convolve(input, kernel1, bias1, convOutput1, inputWidth, inputHeight, inputChannels, outputChannels1, kernelSize, stride, padding);

    // Apply ReLU activation for the first layer
    applyReLU(convOutput1);

    // Perform MaxPooling for the first layer
    const int poolSize = 2;
    const int poolStride = 2;
    const int pooledWidth = inputWidth / poolStride;
    const int pooledHeight = inputHeight / poolStride;

    maxPooling(convOutput1, maxPoolOutput1, inputWidth, inputHeight, outputChannels1, poolSize, poolStride);

    // Read kernel and bias for the second layer
    std::vector<float> kernel2, bias2, convOutput2, maxPoolOutput2;
    readBinaryFile(kernelPath2, kernel2);
    readBinaryFile(biasPath2, bias2);

    // Perform second convolution
    convolve(maxPoolOutput1, kernel2, bias2, convOutput2, pooledWidth, pooledHeight, outputChannels1, outputChannels2, kernelSize, stride, padding);

    // Apply ReLU activation for the second layer
    applyReLU(convOutput2);

    // Perform MaxPooling for the second layer
    const int pooledWidth2 = pooledWidth / poolStride;
    const int pooledHeight2 = pooledHeight / poolStride;

    maxPooling(convOutput2, maxPoolOutput2, pooledWidth, pooledHeight, outputChannels2, poolSize, poolStride);

    // Read kernel and bias for the third layer
    std::vector<float> kernel3, bias3, convOutput3;
    readBinaryFile(kernelPath3, kernel3);
    readBinaryFile(biasPath3, bias3);

    // Perform third convolution
    convolve(maxPoolOutput2, kernel3, bias3, convOutput3, pooledWidth2, pooledHeight2, outputChannels2, outputChannels3, kernelSize, stride, padding);

    // Apply ReLU activation for the third layer
    applyReLU(convOutput3);
    // Dense layer dimensions
    const int denseInputSize = pooledWidth2 * pooledHeight2 * outputChannels3;
    const int denseOutputSize = 512;

    // File paths for Dense layer weights and biases
    std::string denseWeightsPath = "D:/MCW/Assignment-1/data/weights/dense_kernel.bin";
    std::string denseBiasesPath = "D:/MCW/Assignment-1/data/weights/dense_bias.bin";

    // Read weights and biases for Dense layer
    std::vector<float> denseWeights, denseBiases, denseOutput;
    readBinaryFile(denseWeightsPath, denseWeights);
    readBinaryFile(denseBiasesPath, denseBiases);

    // Perform Dense layer
    dense(convOutput3, denseWeights, denseBiases, denseOutput, denseInputSize, denseOutputSize);

    // Apply ReLU activation for Dense layer
    applyReLU(denseOutput);

    // For the second Dense layer
    std::string dense2WeightsPath = "D:/MCW/Assignment-1/data/weights/dense_1_kernel.bin";
    std::string dense2BiasesPath = "D:/MCW/Assignment-1/data/weights/dense_1_bias.bin";
    const int dense2InputSize = denseOutputSize; // Output of first dense layer is input to second
    const int dense2OutputSize = 10;

    std::vector<float> dense2Weights, dense2Biases, dense2Output;
    readBinaryFile(dense2WeightsPath, dense2Weights);
    readBinaryFile(dense2BiasesPath, dense2Biases);

    denseLayerWithSoftmax(denseOutput, dense2Weights, dense2Biases, dense2Output, dense2InputSize, dense2OutputSize);

    std::cout << "Output Shape after second Dense layer: (" << dense2OutputSize << ")" << std::endl;
    float ii = 0.0;
    float jj = 0.0;
    for (int i = 0; i < dense2OutputSize; ++i)
    {
        std::cout << dense2Output[i] << " ";
        if (jj < dense2Output[i])
        {
            jj = dense2Output[i];
            ii = i;
        }
    }
    std::cout << std::endl << ii << " ";
            // 0: Airplane
            // 1: Automobile
            // 2: Bird
            // 3: Cat
            // 4: Deer
            // 5: Dog
            // 6: Frog
            // 7: Horse
            // 8: Ship
            // 9: Truck

    return 0;
}
