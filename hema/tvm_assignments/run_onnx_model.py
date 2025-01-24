import torch
import torch.nn as nn
import numpy as np
import tvm
import onnx
from tvm import relay, relax
from tvm.contrib import graph_executor

# Step 1: Define the PyTorch Model
class TorchModel(nn.Module):
    def __init__(self):
        super(TorchModel, self).__init__()
        self.fc1 = nn.Linear(784, 256)  # Fully connected layer: 784 -> 256
        self.relu1 = nn.ReLU()          # ReLU activation
        self.fc2 = nn.Linear(256, 10)   # Fully connected layer: 256 -> 10

    def forward(self, x):
        x = self.fc1(x)
        x = self.relu1(x)
        x = self.fc2(x)
        return x


# Instantiate the model
pytorch_model = TorchModel()
pytorch_model.eval()  # Set the model to evaluation mode

# Step 2: Export the PyTorch Model to ONNX Format
dummy_input = torch.randn(1, 784)  # Example input tensor
onnx_model_path = "torch_model.onnx"
torch.onnx.export(
    pytorch_model,
    dummy_input,
    onnx_model_path,
    input_names=["input"],
    output_names=["output"],
    opset_version=11,  # Ensure compatibility
)

print(f"ONNX model saved at: {onnx_model_path}")

# Step 3: Import the ONNX Model into TVM
# Load the ONNX model
onnx_model = onnx.load(onnx_model_path)

# Convert the ONNX model to TVM Relay format
input_name = "input"
input_shape = (1, 784)  # Input shape matching the ONNX model
shape_dict = {input_name: input_shape}

mod, params = relay.frontend.from_onnx(onnx_model, shape_dict)

# Step 4: Visualize the Model Before Transformation
# Dump the JSON representation of the model
with open("model_before_transformation.json", "w") as f:
    f.write(tvm.ir.save_json(mod))

# Dump the computation graph as a .dot file
with open("model_before_transformation.dot", "w") as f:
    f.write(str(mod))


# Step 5: Apply Transformations for Optimization
target = tvm.target.Target("llvm")
# print(tvm.target.Target("llvm").kind)
with tvm.transform.PassContext(opt_level=3):
    # Compile the model for the LLVM target (CPU)
    lib = relay.build(mod, target=target, params=params)

# Step 6: Run the Model Using TVM Runtime
# Create TVM runtime and set the input
dev = tvm.cpu(0)
module = graph_executor.GraphModule(lib["default"](dev))

# Generate random input data
input_data = np.random.rand(1, 784).astype("float32")
module.set_input(input_name, input_data)

# Run the model
module.run()

# Get the output
output = module.get_output(0).numpy()
print("Model output:", output)

# Step 7: Visualize the Model After Transformation
# Save the optimized computation graph
optimized_mod = relay.optimize(mod, tvm.target.Target("llvm"), params)

# Step 7: Visualize the Model After Transformation
# Save the JSON representation of the optimized model
with open("model_after_transformation.json", "w") as f:
    f.write(tvm.ir.save_json(optimized_mod))

# Save the optimized computation graph to a .dot file
with open("model_after_transformation.dot", "w") as f:
    f.write(str(optimized_mod))

