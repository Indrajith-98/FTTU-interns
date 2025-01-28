import tvm
from tvm import relay
from tvm.contrib import graph_executor
import numpy as np
import torchvision.models as models
import torch

# Step 1: Load a pre-trained PyTorch model (ResNet-18)
torch_model = models.resnet18(pretrained=True)
torch_model.eval()  # Set the model to evaluation mode

# Step 2: Convert the PyTorch model to Relay IR
input_shape = (1, 3, 224, 224)  # Batch size 1, 3 color channels, 224x224 resolution
input_data = torch.randn(input_shape)
scripted_model = torch.jit.trace(torch_model, input_data).eval()  # TorchScript model

shape_list = [("input0", input_shape)]
mod, params = relay.frontend.from_pytorch(scripted_model, shape_list)

# Step 3: Compile the model with TVM
target = "llvm"  # Target backend (LLVM for CPU)
with tvm.transform.PassContext(opt_level=3):
    lib = relay.build(mod, target=target, params=params)

# Step 4: Load the compiled model
dev = tvm.cpu(0)  # Use CPU for execution
module = graph_executor.GraphModule(lib["default"](dev))

# Step 5: Prepare input data
input_data_np = np.random.uniform(-1, 1, size=input_shape).astype("float32")
module.set_input("input0", input_data_np)

# Step 6: Run the model
module.run()

lib.export_library("resnet_model.so")

# Step 7: Get the output
output = module.get_output(0).asnumpy()
print("Output shape:", output.shape)
