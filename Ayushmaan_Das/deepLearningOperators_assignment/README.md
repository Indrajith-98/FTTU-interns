# Implementing the core functionality of the layers with C++.

- [Project Overview](#project-overview)
- [Project Structure](#project-structure)
- [Key Files](#key-files)
- [Working and Implementation](#working-and-implementation)
- [Sample structure of the `model_config.json` file](#sample-structure-of-the-model_configjson-file)

### Project Overview

1. **Loads an ONNX deep learning model** trained on _FashionMNIST_ [(link to model)](../python_assignments/Deep_Learning_TensorRT/hypertuned_resnet34_fashion_mnist.onnx).
2. **Parses the model configuration** from `configs/` (_ignored in Repo due to large Size_).
3. **Implements core ONNX operations** (like Conv, Relu, Add, etc.).
4. **Executes the model layer by layer** (as per `executor.cpp`).
5. **Logs execution details** (layer name, operation, time, pass/fail) [(check the logs here)](./logs/FINAL_DETAILED_LOGS.txt).

<hr>

### Project Structure

- **`.venv/`** : Virtual environment (ignored in repo).
- **`build/`** : Compiled binaries and object files (ignored in repo).
- **`configs/`** : Stores model configuration (`model_config.json`).
- **`include/`** : C++ header files defining ONNX operators and execution logic.
- **`layer_wise_dumping/`** : Code to generate `model_config.json`.
- **`logs/`** : Stores execution logs [(check here)](./logs/LAYER_WISE_LOGS.txt).
- **`models/`** : ONNX model used for inference (ignored in repo).
- **`onnxruntime/`** : Runtime support for ONNX (ignored in repo).
- **`src/`** : Source codes.

<hr>

### Key Files

- [**`executor.cpp`**](./src/executor.cpp) – Manages model execution by iterating through nodes and applying operations.
- [**`operators.cpp`**](./src/operators.cpp) – Implements ONNX floating-point operations like Conv, Add, Mul, and Relu.
- [**`parser.cpp`**](./src/parser.cpp) – Parses `model_config.json`, extracts graph details, and decodes Base64-encoded weights and shapes.

<hr>

### Working and Implementation

1. **Model Loading**

   - Reads `model_config.json` from `configs/`.
   - Parses the ONNX model.

2. **Operator Execution**

   - Runs [**`executor.cpp`**](./src/executor.cpp), which iterates through layers.
   - Calls functions in [**`operators.cpp`**](./src/operators.cpp) to apply ONNX ops.

3. **Logging & Debugging**
   - Logs details into [`FINAL_DETAILED_LOGS.txt`](./logs/FINAL_DETAILED_LOGS.txt).
   - Dumps results in a detailed logging manner.

<hr>

### Sample structure of the `model_config.json` file

```json
{
  "graph": {
    "input": [{ "name": "input_tensor", "dims": [1, 28, 28] }],
    "initializer": [
      { "name": "weight_1", "dims": [32, 1, 3, 3], "rawData": "..." }
    ],
    "node": [
      {
        "name": "Conv_1",
        "opType": "Conv",
        "input": ["input_tensor", "weight_1"],
        "output": ["conv_out"]
      },
      {
        "name": "Relu_1",
        "opType": "Relu",
        "input": ["conv_out"],
        "output": ["relu_out"]
      }
    ]
  }
}
```

<hr>
