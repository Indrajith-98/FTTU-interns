# Assignment 2: CNN Inference Pipeline in C++

This assignment involves creating a Convolutional Neural Network (CNN) inference pipeline using C++ to replicate the behavior of a trained CNN model. The model is trained on the CIFAR-10 dataset using Python, and its weights, biases, and structural details are extracted into a JSON file. The goal of this project is to demonstrate the correctness of a C++ implementation by comparing its layer-wise results with those of the Python model.

## Project Overview

The implementation consists of the following key components:

### Operators Definition

The operators required for the CNN, such as binary operations, convolution, dense layers, flattening, and pooling, are defined in the utilities directory. These operators form the core building blocks for constructing and executing the model.

- **Binary Operations**: These include element-wise mathematical operations (e.g., addition, multiplication) essential for combining inputs, weights, and biases in a neural network. They are optimized for efficient execution to handle large datasets and tensors.
- **Convolution**: This operator performs the convolutional operation on input data using learned filters. Convolution is critical for feature extraction in images, as it captures spatial hierarchies such as edges, textures, and complex patterns.
- **Dense (Fully Connected) Layer**: The dense layer is responsible for combining all input neurons with weights to produce output neurons. It plays a critical role in decision-making by aggregating features learned in earlier layers.
- **Flattening**: The flatten operation converts multi-dimensional inputs (e.g., feature maps from convolutional layers) into a single-dimensional array. This transformation is necessary to connect convolutional outputs to dense layers for final classification.
- **Pooling**: Pooling layers reduce the spatial dimensions of feature maps while retaining essential information. Common pooling operations include max pooling, which captures the maximum value in a region, and average pooling, which computes the average.

### Main Code Execution

The core of the implementation resides in the `src/main.cpp` file. The main code orchestrates the inference process by reading the JSON file containing the model's structure and parameters. Using this information, the code executes the defined operators (e.g., convolution, pooling, dense) layer by layer.

### Model Comparison and Verification

The extracted weights, biases, and other parameters from the Python-trained model are stored in a JSON file. This file serves as the input for the C++ implementation. By processing a sample input image layer-by-layer, the results from the C++ implementation are compared with those from the Python model to validate correctness.

### Input Classification

A sample image (`resized_image.jpeg`, representing the "dog" class) is provided in the report folder for testing and classification. The image is preprocessed and passed through the implemented CNN, and the final output confirms that the model correctly classifies the image.

## Key Highlights

- **JSON-Based Configuration**: The project leverages a JSON file for storing model parameters and structural details, making it easier to replicate and debug the Python-trained model in C++.
- **Layer-Wise Execution**: By breaking down the CNN inference process into individual layers and operators, the implementation ensures modularity and enables detailed result verification.
- **Cross-Language Comparison**: The project highlights the compatibility of trained models across languages and frameworks, showcasing the portability of machine learning models.

This project demonstrates the successful implementation of a CNN in C++ for inference purposes, with results comparable to a Python-trained model. The correctness of the implementation is validated by accurate classification of the provided test image.