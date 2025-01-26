# CIFAR-10 Python Model

This repository contains a deep learning project focused on building and optimizing a Convolutional Neural Network (CNN) to classify images from the CIFAR-10 dataset. The project emphasizes model architecture design, hyperparameter tuning, latency estimation, and TensorRT conversion for improved performance.

---

## Overview

The project aims to:

1. **Build and Train a Model**:
   - A CNN with three convolutional layers and two dense layers was developed.
   - The model was trained using the CIFAR-10 dataset, which consists of 60,000 32x32 color images in 10 classes.

2. **Optimize Hyperparameters**:
   - Several hyperparameter tuning methods were employed to identify the best-performing configuration.
   - The tuning process involved analyzing accuracy, loss, and other evaluation metrics.

3. **Export Model Configuration**:
   - After identifying the best model, its attributes (e.g., layer configuration, weights, activation functions) were exported to a JSON file for easy reproducibility.

4. **Estimate Latency**:
   - The execution time of each operation in the model was estimated on both CPU and GPU environments.
   - Insights into latency were crucial for performance optimization.

5. **Convert to TensorRT**:
   - The optimized model was converted into a TensorRT model to leverage faster inference and reduced latency.
   - Performance improvements were observed in both execution speed and resource utilization.

---

## Features

- Custom CNN model for image classification.
- Comprehensive hyperparameter tuning.
- Export model architecture and parameters to a JSON file.
- Latency analysis on CPU and GPU for each operation.
- Conversion to TensorRT for enhanced performance.

---

## Layer wise Output dimensions and number of parameters

![image](https://github.com/user-attachments/assets/22aafa69-b519-43f3-92ad-410c12dd9bdf)


 - Total params: 562,316 (2.15 MB)
 - Trainable params: 562,314 (2.15 MB)
 - Non-trainable params: 0 (0.00 B)
 - Optimizer params: 2 (12.00 B)

--- 

## Technologies Used

- **Programming Language**: Python
- **Libraries**:
  - TensorFlow/Keras (for model development and training)
  - NumPy (for numerical operations)
  - TensorRT (for model optimization and inference)
  - JSON (for saving and loading model configurations)

---

## Results

- The best configuration achieved an accuracy of 76% on the CIFAR-10 test set.
- **Latency analysis**:
  - Average latency for the original model:
    - CPU: 0.21 s
    - GPU: 0.41 s
  - Average latency for the TensorRT model:
    - Single inference latency: 0.0027 s
    - Batch inference latency (batch_size=64): 12.533 s

---
