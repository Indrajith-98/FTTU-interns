import os
import json

# Define paths
input_dir = "./data/input"
output_dir = "./data/output"
config_path = "./configs/json/config.json"

# Get list of input .bin files
input_files = sorted([f for f in os.listdir(input_dir) if f.endswith(".bin")])

# Check if there are images in input folder
if not input_files:
    print("❌ ERROR: No input files found in `data/input/`. Run the conversion script first!")
    exit(1)

# Generate layers dynamically
layers = []
for i, file in enumerate(input_files):
    input_file = os.path.join(input_dir, file)
    conv_output = os.path.join(output_dir, f"cifar_conv_output_{i}.bin")
    relu_output = os.path.join(output_dir, f"cifar_relu_output_{i}.bin")
    final_output = os.path.join(output_dir, f"final_output_{i}.bin")

    # Convolution Layer
    layers.append({
        "name": f"Conv_{i}",
        "type": "Conv",
        "input": [input_file],
        "output": [conv_output],
        "attributes": {
            "kernel_shape": [3, 3],
            "strides": [1, 1],
            "pads": [1, 1, 1, 1]
        }
    })

    # ReLU Activation
    layers.append({
        "name": f"ReLU_{i}",
        "type": "ReLU",
        "input": [conv_output],
        "output": [relu_output],
        "attributes": {}
    })

    # Softmax Activation
    layers.append({
        "name": f"Softmax_{i}",
        "type": "Softmax",
        "input": [relu_output],
        "output": [final_output],
        "attributes": {}
    })

# Create final config dictionary
config = {
    "test_type": "model",
    "layers": layers
}

# Save JSON config
os.makedirs(os.path.dirname(config_path), exist_ok=True)
with open(config_path, "w") as f:
    json.dump(config, f, indent=4)

print(f"✅ Config file generated: {config_path}")
print(f"🔹 Number of images processed: {len(input_files)}")
