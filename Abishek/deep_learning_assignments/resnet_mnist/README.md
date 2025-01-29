# **DeepLearning Assignment**

## **Task Overview**
This task involves training a ResNet model using TensorFlow on the MNIST dataset, followed by hyperparameter tuning, data augmentation and performance optimization.

### **Section 1: Model Training**
* Train a ResNet model on MNIST until the training saturates and report the F1 score.
* Perform hyperparameter tuning using Random Search and report the updated scores after each adjustment.
* Apply data augmentations to improve generalization and evaluate their impact on performance.

### **Section 1: Inference**
* Base model F1-Score: 0.98
* Best param model F1-Score: 0.97
* Data augmented model: 0.99

### **Section 2: Model Optimization using TensorRT**
Based on inference from Section 1, I have chosen the data augmented model as the final model, then converted the h5 model to onnx and optimized the onnx model using TensorRT.

### **Section 2: Inference**
H5 Model Accuracy: 98.82%
TRT Model Accuracy: 98.83%

H5 Model Latency: 0.132996 seconds
TRT Model Latency: 0.004294 seconds

## **Project Folder Contents**

### **.gitignore**
Ensures unnecessary files are not tracked in the Git repository.

### **base_model.ipynb**
Jupyter Notebook File which contains the code for training and inferencing the base resnet model.

### **final_model.ipynb**
Jupyter Notebook File which contains the code for training and inferencing the data augmented resnet model.

### **hypertuned_model.ipynb**
Jupyter Notebook File which contains the code for training and inferencing the model with best params obtained from hyper parameter tuning.

### **mnist_base_resnet.h5**
The Base Model in H5 Format.

### **mnist_data_aug_resnet.h5**
The Data Augmented model in H5 Format.

### **mnist_hyp_tuned_resnet.h5**
The Hyper Parameter tuned model in H5 Format.

### **mnist_resnet_final.onnx**
The Final Best Model in ONNX Format.

### **mnist_resnet_final.trt**
The Optimized Model using TensorRT.

### **tensorrt_latency.ipynb**
The Jupyter Notebook File which compares the latency of H5 and TRT Model.

### **tf2onnx.ipynb**
The Jupyter Notebook File which contains the code to convert H5 to ONNX Model.