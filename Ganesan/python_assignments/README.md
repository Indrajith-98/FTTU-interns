# ResNet18 Model Optimization and Deployment

## Project Overview
This project focuses on training and optimizing a **ResNet-18** model using **PyTorch** or **TensorFlow**. The trained model is converted to **ONNX** format and optimized with **TensorRT** to enhance inference performance.

## Features
- Model training using PyTorch or TensorFlow.
- Hyperparameter tuning and data augmentation to improve the F1 score.
- Conversion of the trained model to ONNX format.
- Optimization using TensorRT for improved inference speed.
- Latency measurement before and after optimization.

## Requirements
To run this project, ensure you have the following dependencies installed:
- Python 3.x
- PyTorch or TensorFlow
- ONNX & ONNX Runtime
- TensorRT (CUDA 12.x)

## Usage
Follow these steps to train and optimize the model:

1. **Train the model**  
   ```bash
   python train.py
