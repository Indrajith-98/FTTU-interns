#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "utils/include/FileUtils.h"
#include "utils/include/ResultUtils.h"
#include "utils/include/LogUtils.h"
#include "conv.h"
#include "prelu.h"
#include "batch_norm.h"
#include "max_pool.h"
#include "flatten.h"
#include "dense.h"
#include "selu.h"
#include "softmax.h"
#include "Test_Operators/include/conv_test.h"
#include "Test_Operators/include/prelu_test.h"
#include "Test_Operators/include/batch_norm_test.h"
#include "Test_Operators/include/max_pool_test.h"
#include "Test_Operators/include/flatten_test.h"
#include "Test_Operators/include/dense_test.h"
#include "extern/json.hpp"  

using json = nlohmann::json;

std::vector<int> parseShape(const nlohmann::json& shape) {
    std::vector<int> result;
    for (const auto& dim : shape) {
        if (dim.is_null()) {
            result.push_back(-1);  // Replace null with -1 or another placeholder
        } else {
            result.push_back(dim.get<int>());
        }
    }
    return result;
}

int main() {

    std::string imagePath = "../data/input/bird.json";
    std::string modelPath = "../configs/json/model_config_details.json";
    std::vector<std::vector<std::vector<double>>> image_matrix;
    json modelConfig;

    try {
        image_matrix = FileUtils::read_image_matrix(imagePath);
        FileUtils::display_image_shape(image_matrix);

        modelConfig = FileUtils::read_model_config(modelPath);
        unitTestLogExecution("Unit Test Results : ",imagePath);
        
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    std::vector<std::vector<std::vector<double>>> output;

    std::map<std::string, std::vector<std::vector<std::vector<double>>>> layer3d_outputs;
    std::map<std::string, std::vector<double>> layer1d_outputs;

    int i=0,j=1;
    while (i<15)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        json cnnlayerConfig = modelConfig["layers"][i++];
        try {
            int filters = cnnlayerConfig["filters"];
            std::vector<int> input_shape = parseShape(cnnlayerConfig["input_shape"]);
            std::vector<int> output_shape = parseShape(cnnlayerConfig["output_shape"]);
            std::vector<int> kernel_size = cnnlayerConfig["kernel_size"].get<std::vector<int>>();
            std::vector<int> strides = cnnlayerConfig["strides"].get<std::vector<int>>();
            std::string padding = cnnlayerConfig["padding"];
            std::vector<int> weights_shape = cnnlayerConfig["weights_shape"].get<std::vector<int>>();
            std::vector<double> weights = cnnlayerConfig["weights"].get<std::vector<double>>();
            std::vector<double> biases = cnnlayerConfig["biases"].get<std::vector<double>>();
            ConvLayer convLayer;
            convLayer.setAttributes(filters, input_shape, output_shape, kernel_size, strides, padding, weights_shape, weights, biases);
            if(i==1)
            {
                output = convLayer.convolve(image_matrix);
            }
            else
            {
                output = convLayer.convolve(output);
            }
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = endTime - startTime;
            logExecution(imagePath,cnnlayerConfig["layer_name"], "convolve", duration.count(), "Pass");
            layer3d_outputs[cnnlayerConfig["layer_name"]]=output;
        } catch (const std::exception& e) {
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = endTime - startTime;
            logExecution(imagePath,cnnlayerConfig["layer_name"], "convolve", duration.count(), "Fail");
            logExecution(imagePath,cnnlayerConfig["layer_name"], "convolve operation Error", duration.count(), e.what());
        }

        std::cout << "Output feature map dimensions after conv "<<j<<"\t\t  :  " << output.size() << "x" << output[0].size() << "x" << output[0][0].size() << std::endl;

        ConvTest :: checkConvLayerOutput(imagePath,cnnlayerConfig["layer_name"],output);
        unitTestLogExecution(cnnlayerConfig["layer_name"].get<std::string>()+" layer operation was executed");

        // PRELU Layer
        startTime = std::chrono::high_resolution_clock::now();
        json prelu1layerConfig = modelConfig["layers"][i++];
        try {
            std::vector<std::vector<std::vector<double>>> alpha_values = prelu1layerConfig["alpha"].get<std::vector<std::vector<std::vector<double>>>>();
            PReLU prelu_layer(alpha_values);
            output = prelu_layer.applyPReLU(output);
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = endTime - startTime;
            logExecution(imagePath,prelu1layerConfig["layer_name"], "applyPReLU", duration.count(), "Pass");
            layer3d_outputs[prelu1layerConfig["layer_name"]]=output;
        }
        catch (const std::exception& e) {
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = endTime - startTime;
            logExecution(imagePath,prelu1layerConfig["layer_name"], "applyPReLU", duration.count(), "Fail");
            logExecution(imagePath,prelu1layerConfig["layer_name"], "apply PReLU operation Error", duration.count(), e.what());
        }

        std::cout << "Output feature map dimensions after prelu "<<j<<"\t\t  :  " << output.size() << "x" << output[0].size() << "x" << output[0][0].size() << std::endl;
        
        PReluTest :: checkPReluLayerOutput(imagePath,prelu1layerConfig["layer_name"],output);
        unitTestLogExecution(prelu1layerConfig["layer_name"].get<std::string>()+" layer operation was executed");

        // Batch Normalization Layer

        startTime = std::chrono::high_resolution_clock::now();    
        json batchnormConfig = modelConfig["layers"][i++];
        try {
            std::vector<double> gamma = batchnormConfig["gamma"].get<std::vector<double>>();
            std::vector<double> beta = batchnormConfig["beta"].get<std::vector<double>>();
            std::vector<double> moving_mean = batchnormConfig["moving_mean"].get<std::vector<double>>();
            std::vector<double> moving_variance = batchnormConfig["moving_variance"].get<std::vector<double>>();
            double epsilon = batchnormConfig["epsilon"];
            BatchNorm batch_norm(gamma, beta, moving_mean, moving_variance, epsilon);
            output = batch_norm.applyBatchNorm(output);
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = endTime - startTime;
            logExecution(imagePath,batchnormConfig["layer_name"], "applyBatchNorm", duration.count(), "Pass");
            layer3d_outputs[batchnormConfig["layer_name"]]=output;
        }catch (const std::exception& e) {
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = endTime - startTime;
            logExecution(imagePath,batchnormConfig["layer_name"], "applyBatchNorm", duration.count(), "Fail");
            logExecution(imagePath,batchnormConfig["layer_name"], "apply Batch Norm operation Error", duration.count(), e.what());
        }

        std::cout << "Output feature map dimensions after batch normalization "<<j<<" :  " << output.size() << "x" << output[0].size() << "x" << output[0][0].size() << std::endl;

        BatchNormTest :: checkBatchNormLayerOutput(imagePath,batchnormConfig["layer_name"],output);
        unitTestLogExecution(batchnormConfig["layer_name"].get<std::string>()+" layer operation was executed");

        // Max Pooling Layer

        startTime = std::chrono::high_resolution_clock::now();    
        json maxpoollayerConfig = modelConfig["layers"][i++];
        try{
            std::vector<int> pool_size = maxpoollayerConfig["pool_size"].get<std::vector<int>>();
            std::vector<int> pstrides = maxpoollayerConfig["strides"].get<std::vector<int>>();
            MaxPool max_pool(pool_size, pstrides);
            output = max_pool.applyMaxPool(output);
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = endTime - startTime;
            logExecution(imagePath,maxpoollayerConfig["layer_name"], "apply MaxPool", duration.count(), "Pass");
            layer3d_outputs[maxpoollayerConfig["layer_name"]]=output;
        }
        catch (const std::exception& e) {
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = endTime - startTime;
            logExecution(imagePath,maxpoollayerConfig["layer_name"], "applyMaxPool", duration.count(), "Fail");
            logExecution(imagePath,maxpoollayerConfig["layer_name"], "apply MaxPooling operation Error", duration.count(), e.what());
        }
        std::cout << "Output feature map dimensions after max pooling "<<j<<"\t  :  " << output.size() << "x" << output[0].size() << "x" << output[0][0].size() << std::endl;

        MaxPoolTest :: checkMaxPoolLayerOutput(imagePath,maxpoollayerConfig["layer_name"],output);
        unitTestLogExecution(maxpoollayerConfig["layer_name"].get<std::string>()+" layer operation was executed");

        i++;
        j++;
    }

    std::vector<double> flattened_map;
    std::vector<double> activated_denseoutput1;
    std::vector<double> normoutput;

    // Flatten

    auto startTime = std::chrono::high_resolution_clock::now();
    try{
        Flatten flatten_layer;
        flattened_map = flatten_layer.flatten(output);
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = endTime - startTime;
        logExecution(imagePath,"flatten", "flatten", duration.count(), "Pass");    
        layer1d_outputs["flatten"]=flattened_map;
        std::cout<<"Flattened Map Size \t\t\t\t\t  :  "<<flattened_map.size()<< std::endl;
        FlattenTest :: checkFlattenOutput(imagePath,"flatten",flattened_map);
        unitTestLogExecution("flatten layer operation was executed");
    }catch (const std::exception& e) {
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = endTime - startTime;
        logExecution(imagePath,"flatten", "flatten", duration.count(), "Fail");
        logExecution(imagePath,"flatten", "flatten operation Error", duration.count(), e.what());
    }
    
    // Dense Layer 1

    startTime = std::chrono::high_resolution_clock::now();
    json dense1layerConfig = modelConfig["layers"][16];
    try{
        float units = dense1layerConfig["units"];
        Dense denseLayer(flattened_map.size(), units);
        std::vector<double> weights = dense1layerConfig["weights"].get<std::vector<double>>();
        std::vector<double> biases = dense1layerConfig["biases"].get<std::vector<double>>();
        denseLayer.setWeights(weights);
        denseLayer.setBiases(biases);
        std::vector<double> dense1output = denseLayer.applyDenseLayer(flattened_map);

        std::cout<<"Dense 1 Layer Output Size \t\t\t\t  :  "<<dense1output.size()<<std::endl;

        // SELU Activation

        SELU selu;
        activated_denseoutput1 = selu.apply(dense1output);
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = endTime - startTime;
        logExecution(imagePath,dense1layerConfig["layer_name"], "apply_dense_with_selu", duration.count(), "Pass");    
        layer1d_outputs[dense1layerConfig["layer_name"]]=activated_denseoutput1;
        DenseTest :: checkDenseLayerOutput(imagePath,dense1layerConfig["layer_name"],activated_denseoutput1);

        unitTestLogExecution(dense1layerConfig["layer_name"].get<std::string>()+" layer operation was executed");
        std::cout<<"Output Size after Selu applied \t\t\t\t  :  "<<activated_denseoutput1.size()<<std::endl;
    }catch (const std::exception& e) {
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = endTime - startTime;
        logExecution(imagePath,dense1layerConfig["layer_name"], "apply_dense_with_selu", duration.count(), "Fail");
        logExecution(imagePath,dense1layerConfig["layer_name"], "apply dense operation Error", duration.count(), e.what());
    }
    
    // Batch Normalization

    startTime = std::chrono::high_resolution_clock::now();
    json batchnormConfig = modelConfig["layers"][17];
    try{
        std::vector<double> gamma = batchnormConfig["gamma"].get<std::vector<double>>();
        std::vector<double> beta = batchnormConfig["beta"].get<std::vector<double>>();
        std::vector<double> moving_mean = batchnormConfig["moving_mean"].get<std::vector<double>>();
        std::vector<double> moving_variance = batchnormConfig["moving_variance"].get<std::vector<double>>();
        float epsilon = batchnormConfig["epsilon"];
        BatchNorm batch_norm(gamma, beta, moving_mean, moving_variance, epsilon);
        normoutput = batch_norm.applyBatchNorm(activated_denseoutput1);
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = endTime - startTime;
        logExecution(imagePath,batchnormConfig["layer_name"], "applyBatchNorm", duration.count(), "Pass");    
        layer1d_outputs[batchnormConfig["layer_name"]]=normoutput;
        BatchNormTest :: checkBatchNormLayerOutput(imagePath,batchnormConfig["layer_name"],normoutput);
        unitTestLogExecution(batchnormConfig["layer_name"].get<std::string>()+" layer operation was executed");
        std::cout << "Output feature map dimensions after batch normalization   :  " << normoutput.size() <<std::endl;   
    }catch (const std::exception& e) {
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = endTime - startTime;
        logExecution(imagePath,batchnormConfig["layer_name"], "applyBatchNorm", duration.count(), "Fail");
        logExecution(imagePath,batchnormConfig["layer_name"], "apply batch norm operation Error", duration.count(), e.what());
    }
    
    // Output Layer

    startTime = std::chrono::high_resolution_clock::now();
    json dense2layerConfig = modelConfig["layers"][19];
    try{
        float units2 = dense2layerConfig["units"];
        Dense denseLayer2(normoutput.size(), units2);
        std::vector<double> weights2 = dense2layerConfig["weights"].get<std::vector<double>>();
        std::vector<double> biases2 = dense2layerConfig["biases"].get<std::vector<double>>();
        denseLayer2.setWeights(weights2);
        denseLayer2.setBiases(biases2);
        std::vector<double> outputlayer = denseLayer2.applyDenseLayer(normoutput);

        std::cout<<"Output (Dense 2) layer Size \t\t\t\t  :  "<<outputlayer.size()<<std::endl;

        // Softmax Activation

        Softmax softmax;
        std::vector<double> probabilities = softmax.applySoftmax(outputlayer);
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = endTime - startTime;
        logExecution(imagePath,dense2layerConfig["layer_name"], "apply_dense_with_softmax", duration.count(), "Pass");    
        layer1d_outputs[dense2layerConfig["layer_name"]]=probabilities;
        DenseTest :: checkDenseLayerOutput(imagePath,dense2layerConfig["layer_name"],probabilities);
        unitTestLogExecution(dense2layerConfig["layer_name"].get<std::string>()+" layer operation was executed");
        ResultUtils :: appendPrediction(imagePath, probabilities, layer3d_outputs, layer1d_outputs);
    }catch (const std::exception& e) {
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = endTime - startTime;
        logExecution(imagePath,dense2layerConfig["layer_name"], "apply_dense_with_softmax", duration.count(), "Fail");
        logExecution(imagePath,dense2layerConfig["layer_name"], "apply dense operation Error", duration.count(), e.what());
    } 
    
    return 0;
}
