# TVM Assignment
- ***Ayushmaan Das (I000452)***

### Problem Statement
- Install TVM from open source (github).
- Prepare basic script to load, compile and run a model on TVM.
- Apply few transformation passes to optimize the model and then visualize the updated IR module.

<hr>

### Instructions
- To run the project:
    - `sudo apt install -y llvm`
    - `pip3 install apache-tvm`
    - `python3 run main.py`
- The **Logs** for Compilation, Optimization and Inferences can be viewed [here](./logs/main.log).
- To **Visualize the Model**, execute: `./visualize_optimized_model.sh` or check the [image](./optimized_tvm_model.png).

<hr>

### Project Structure

```
tvm_assignments/
│── models/
│   └── hypertuned_resnet34_fashion_mnist.onnx        # Not in repo (large size)
│
│── compiled_tvm_model/            # Folder for storing compiled TVM
│
│── scripts/
│   │── load_model.py              # Loads the ONNX model and converts to Relay
│   │── optimize_model.py          # Applies optimization passes
│   │── compile_model.py           # Compiles the model and saves 
│   │── run_inference.py           # Loads and runs the compiled model
│   └── logger.py                  # Logger
│
│── logs/                          # Detailed logging for compilation and inferences

│── main.py                        # Main script 
│── visualize_optimized_model.sh   # To visualize model using Netron
│── requirements.txt               # Python dependencies
```

<hr>

### Visualization of Optimied Model

![netron_graph](./optimized_tvm_model.png)

<hr>