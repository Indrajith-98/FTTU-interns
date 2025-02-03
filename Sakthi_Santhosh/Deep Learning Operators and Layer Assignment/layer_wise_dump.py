import numpy as np
import os
import tensorflow as tf

# Function to save numpy array to binary file
def dump_to_bin(data, file_path):
    data.tofile(file_path)

# Directories for storing input, weights, and output data
input_dir = 'data/input_data'
weight_dir = 'D:/data/weights_data'
output_dir = 'data/output_data'

# Ensure directories exist
os.makedirs(input_dir, exist_ok=True)
os.makedirs(weight_dir, exist_ok=True)
os.makedirs(output_dir, exist_ok=True)

# Example Keras/TensorFlow model (replace with your actual model)
model = tf.keras.applications.MobileNetV2(weights='imagenet')

# Process each layer in the model
for layer in model.layers:
    print(f"Layer: {layer.name}")
    
    # 1. **Input Data**: Generate dummy input data based on input shape
    input_shape = layer.input.shape[1:]  # Ignore batch dimension
    input_data = np.random.rand(1, *input_shape)  # Generate dummy input
    
    # Save input data for Conv2D layers and others
    input_file_path = os.path.join(input_dir, f"{layer.name}_input.bin")
    dump_to_bin(input_data, input_file_path)

    # 2. **Weights**: Extract weights and biases of the layer
    weights = layer.get_weights() if hasattr(layer, 'get_weights') else []
    
    if weights:
        for idx, weight in enumerate(weights):
            weight_file_path = os.path.join(weight_dir, f"{layer.name}_weight_{idx}.bin")
            dump_to_bin(weight, weight_file_path)

    # 3. **Output Data**: Generate dummy output (in real use, pass actual input to get output)
    output_shape = layer.output.shape[1:]  # Ignore batch dimension
    output_data = np.random.rand(1, *output_shape)  # Dummy output
    output_file_path = os.path.join(output_dir, f"{layer.name}_output.bin")
    dump_to_bin(output_data, output_file_path)

    # Optional: Log layer details for debugging/reference
    print(f"  Input Shape: {input_shape}")
    print(f"  Output Shape: {output_shape}")
    if weights:
        print(f"  Number of Weights: {len(weights)}")
        for i, weight in enumerate(weights):
            print(f"    Weight {i}: Shape {weight.shape}")
    print("-" * 50)

print("Layer-wise dump completed!")
