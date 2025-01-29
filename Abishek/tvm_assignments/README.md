# **Python Assignment**

## **Task Overview**
This task involves loading a pre-trained ResNet ONNX model for MNIST, defining its input shape and compilation target (LLVM for CPU), and converting the model to TVM Relay IR for optimization. The model is then compiled with TVM's optimization passes to enhance efficiency. Using GraphExecutor, inference is run on a randomly generated input, and the output is retrieved. Finally, the optimized model is saved as a shared library (tvm_model.so), and the computational graph is exported to a JSON file (compiled_graph.json).

## **Project Folder Contents**

### **compiled_graph.json**
The computational graph of the model for visualization purposes.

### **mnist_resnet_final.onnx**
The pretrained resnet model in ONNX Format.

### **onnx2tvm.ipynb**
The Jupyter Notebook file which contains the code to optimize and deploy the model on llvm.

### **tvm_model.so**
The Optimized model tailored to be deployed efficiently in LLVM.