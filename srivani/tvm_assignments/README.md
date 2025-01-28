# ONNX to TVM Model Inference
This project demonstrates the process of loading an ONNX model, converting it to TVM's Relay intermediate representation (IR), optimizing the model, 
compiling it for execution, and running inference on a sample image.

## Prerequisites
Ensure you have the following libraries installed: <br>

onnx: For loading and parsing ONNX models. <br>

tvm: For converting the model, optimizing, compiling, and running the inference. <br>

numpy: For numerical operations. <br>

opencv-python: For image loading and preprocessing. <br>

`pip install onnx tvm numpy opencv-python`

## Run the code

`python onnx_to_tvm_inference.py`

## Workflow
This project follows the steps outlined below to perform model inference: <br>

### Step 1: Load the ONNX Model

The ONNX model (best_model_final.onnx) is loaded into the script using the onnx library.

### Step 2: Convert the ONNX Model to Relay IR
The ONNX model is then converted into the TVM Relay Intermediate Representation (IR). This step is crucial as Relay provides an efficient way to represent and optimize machine learning models.

### Step 3: Display Input Details and Set the Input Shape
The input details of the ONNX model are displayed. The input shape is set explicitly based on the model's requirements. In this case, the input shape is set to (100, 3, 32, 32) to match the model's expected input dimensions.

### Step 4: Apply Explicit Optimization Passes
A series of custom optimization passes are applied to the Relay model:

**SimplifyInference:** Simplifies the model's inference operations. <br>

**FoldConstant:** Folds constant expressions into simpler expressions. <br>

**EliminateCommonSubexpr:** Removes common subexpressions in the computation graph. <br>

**AlterOpLayout:** Alters the operator layout for performance. <br>

**FuseOps:** Fuses multiple operations into a single operator. <br>

### Step 5: Compile the Optimized Model
The optimized Relay model is compiled to a target device (in this case, a CPU with the target "llvm"). This step converts the optimized model into an executable format.

### Step 6: Load and Preprocess the Image
An image (Pic.jpg) is loaded and preprocessed to match the input format expected by the model:
```
The image is resized to (32, 32) pixels.
It is normalized to a range of [0, 1].
The dimensions are converted from HWC (height, width, channels) to CHW (channels, height, width).
The image is expanded with a batch dimension and tiled to create a batch size of 100 (to match the model's input size).
```

### Step 7: Run Inference
Inference is performed using the compiled model. The preprocessed image is fed as input to the model, and the output is computed.

### Step 8: Get the Output
The output of the model is retrieved. The average output across the batch is computed, and the predicted class is determined by finding the index of the maximum value.

### Step 9: Interpret the Prediction
The predicted class is interpreted based on a predefined list of class names (class_names). The final predicted class is printed to the console.

## Project structure

├── best_model_final.onnx      # ONNX model file <br>
├── Pic.jpg                   # Sample input image <br>
├── tvm_1.py   # Python script performing the workflow <br>
├── README.md                 # Project README <br>

