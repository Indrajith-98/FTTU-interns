import onnx
import tvm
from tvm import relay, transform
import numpy as np
import cv2 

# Load the ONNX model
onnx_model = onnx.load("c3d2best.onnx")
print("ONNX model loaded successfully.")

# Convert the ONNX model to Relay IR
relay_model, params = relay.frontend.from_onnx(onnx_model)
print("ONNX model successfully converted to Relay IR.")

# Display input details and set the input shape
print("Model inputs:")
for input_tensor in onnx_model.graph.input:
    print(f"Name: {input_tensor.name}, Shape: {input_tensor.type.tensor_type.shape}")

input_name = onnx_model.graph.input[0].name
input_shape = (1, 32, 32, 3) 
shape_dict = {input_name: input_shape}

# Reload model with the correct input shape
relay_model, params = relay.frontend.from_onnx(onnx_model, shape=shape_dict)
print(f"Input name: {input_name}, Input shape set to {input_shape}")

# Verify relay_model is an IRModule
if not isinstance(relay_model, tvm.IRModule):
    raise ValueError(f"Expected tvm.IRModule, but got {type(relay_model)}")

# Apply explicit optimization passes
print("\nApplying custom optimization passes...")
passes = [
    relay.transform.SimplifyInference(), 
    relay.transform.FoldConstant(),      
    relay.transform.EliminateCommonSubexpr(), 
    relay.transform.AlterOpLayout(),    
    relay.transform.FuseOps(),
]

seq = tvm.transform.Sequential(passes)

# Apply optimization passes
with tvm.transform.PassContext(opt_level=3):
    optimized_relay_model = seq(relay_model)

# Verify the optimized Relay model is an IRModule
if not isinstance(optimized_relay_model, tvm.IRModule):
    raise ValueError(f"Expected tvm.IRModule after optimization, but got {type(optimized_relay_model)}")

# Step 5: Visualize the IR before and after optimization
print("\nOriginal Relay IR:")
print(relay_model)

print("\nOptimized Relay IR:")
print(optimized_relay_model)

# Save the optimized IR to a file
with open("optimized_relay_model.txt", "w") as f:
    f.write(str(optimized_relay_model))

print("Optimized Relay IR saved to 'optimized_relay_model.txt'.")

# Compile the optimized model
target = "llvm" 
print("\nCompiling the optimized model...")
lib = relay.build(optimized_relay_model, target=target, params=params)
print("Model successfully compiled.")

# Load and preprocess the image
img = cv2.imread("img3.jpg")
img = cv2.resize(img, (32, 32))  
img = img.astype(np.float32) / 255.0  
img = np.expand_dims(img, axis=0)

# Run inference
dev = tvm.cpu(0) 
module = tvm.contrib.graph_executor.GraphModule(lib["default"](dev))
module.set_input(input_name, img)
module.run()


output = module.get_output(0).asnumpy()
print("\nModel inference result:")
print(output)

class_names = ['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']
predicted_class = np.argmax(output)
print(f"Predicted class: {class_names[predicted_class]}")