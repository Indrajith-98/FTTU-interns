import onnx
import tvm
from tvm import relay, transform
import numpy as np
import cv2

# Define file paths
onnx_model_path = "/home/ayushkr/tvm_project/c3d2best.onnx"
image_path = "/home/ayushkr/tvm_project/DOG_picture.jpg"

# Step 1: Load the ONNX model
onnx_model = onnx.load(onnx_model_path)  # Load the model from the correct path
print("ONNX model loaded successfully.")

# Step 2: Convert the ONNX model to Relay IR
relay_model, params = relay.frontend.from_onnx(onnx_model)
print("ONNX model successfully converted to Relay IR.")

print("Model inputs:")
for input_tensor in onnx_model.graph.input:
    print(f"Name: {input_tensor.name}, Shape: {input_tensor.type.tensor_type.shape}")

input_name = onnx_model.graph.input[0].name
input_shape = (1, 32, 32, 3)  # Adjust the shape as per your model input
shape_dict = {input_name: input_shape}

# Step 4: Reload model with the correct input shape
relay_model, params = relay.frontend.from_onnx(onnx_model, shape=shape_dict)
print(f"Input name: {input_name}, Input shape set to {input_shape}")

# Step 5: Verify relay_model is an IRModule
if not isinstance(relay_model, tvm.IRModule):
    raise ValueError(f"Expected tvm.IRModule, but got {type(relay_model)}")

# Step 6: Apply optimization passes
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

# Step 7: Verify optimized model
if not isinstance(optimized_relay_model, tvm.IRModule):
    raise ValueError(f"Expected tvm.IRModule after optimization, but got {type(optimized_relay_model)}")

# Step 8: Visualize IR before and after optimization
print("\nOriginal Relay IR:")
print(relay_model)

print("\nOptimized Relay IR:")
print(optimized_relay_model)

# Step 9: Save the optimized IR to a file
with open("/home/ayushkr/tvm_project/optimized_relay_model.txt", "w") as f:
    f.write(str(optimized_relay_model))

print("Optimized Relay IR saved to 'optimized_relay_model.txt'.")

# Step 10: Compile the optimized model
target = "llvm"  # For CPU (use "cuda" for GPU)
print("\nCompiling the optimized model...")
lib = relay.build(optimized_relay_model, target=target, params=params)
print("Model successfully compiled.")

# Step 11: Load and preprocess the image (input)
img = cv2.imread(image_path)  # Ensure the correct path
if img is None:
    raise FileNotFoundError(f"Error: Image file not found at {image_path}")

img = cv2.resize(img, (32, 32))  
img = img.astype(np.float32) / 255.0  
img = np.expand_dims(img, axis=0)

# Step 12: Run inference
dev = tvm.cpu(0)  # If using GPU, change to tvm.gpu(0)
module = tvm.contrib.graph_executor.GraphModule(lib["default"](dev))
module.set_input(input_name, img)
module.run()

output = module.get_output(0).asnumpy()
print("\nModel inference result:")
print(output)

# Step 13: Get predicted class (example: for image classification)
class_names = ['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']
predicted_class = np.argmax(output)
print(f"Predicted class: {class_names[predicted_class]}")

