import os
import numpy as np
import tensorflow as tf
from PIL import Image
import cv2

def save_layer_outputs_as_1d(model, input_data, output_dir):
    """Save the outputs of each layer as a 1D array to files."""
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    layer_outputs = [layer.output for layer in model.layers]  # Get outputs of all layers
    intermediate_model = tf.keras.models.Model(inputs=model.input, outputs=layer_outputs)
    
    # Get outputs for the input data
    outputs = intermediate_model.predict(input_data)
    
    for i, output in enumerate(outputs):
        layer_name = model.layers[i].name
        output_file = os.path.join(output_dir, f"{layer_name}.txt")
        
        with open(output_file, "w") as f:
            
            # Flatten the output to 1D and save each value on a new line
            flattened_output = output.flatten()
            np.savetxt(f, flattened_output, fmt="%.6f")

        print(f"Saved output for {layer_name} to {output_file}")

# Load and preprocess the input image
image = cv2.imread("F:/MultiCoreWare/Assignment 1/test_images/test_image_4.jpeg", cv2.IMREAD_COLOR)
image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
resized_image = cv2.resize(image, (32, 32))
normalized_image = resized_image.astype(np.float32) / 255.0
image_array = np.expand_dims(normalized_image, axis=0)

# Load the model
model = tf.keras.models.load_model("F:/MultiCoreWare/Assignment 1/models/keras/augmented_model.keras")

# Save the outputs to a directory
output_directory = "F:/MultiCoreWare/C++ Application/Project_Root/data/python_layer_outputs"
save_layer_outputs_as_1d(model, image_array, output_directory)
