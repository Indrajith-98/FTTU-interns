import numpy as np
import onnxruntime as ort
import os

# Paths 
onnx_model_path = '/mnt/c/Users/prasa/OneDrive/Desktop/cpp_assignment/DeepLearningProject/model/cifar10_resnet18_17_c.onnx'

input_dir = "../data/input"
output_dir = "../data/reference"
os.makedirs(output_dir, exist_ok=True)

# Load ONNX model
session = ort.InferenceSession(onnx_model_path)

# Get correct input name
input_name = session.get_inputs()[0].name  # Get correct input name from ONNX model
input_shape = session.get_inputs()[0].shape
print(f"✅ ONNX Model Input Name: {input_name}, Expected Shape: {input_shape}")

# Process each input .bin file
for file in sorted(os.listdir(input_dir)):
    if not file.endswith(".bin"):
        continue

    input_path = os.path.join(input_dir, file)
    output_path = os.path.join(output_dir, file.replace("image", "output"))

    # Load input data
    input_data = np.fromfile(input_path, dtype=np.float32).reshape(1, 32, 32, 3)  # NHWC

    # Run ONNX inference
    outputs = session.run(None, {input_name: input_data})[0]

    # Save reference output
    outputs.tofile(output_path)
    print(f"✅ Reference output saved: {output_path}")
