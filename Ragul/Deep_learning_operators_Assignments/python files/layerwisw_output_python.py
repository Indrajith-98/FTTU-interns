import os
import numpy as np
import tensorflow as tf
from tensorflow.keras.preprocessing import image

def load_model(model_path):
    """Load the trained model."""
    return tf.keras.models.load_model(model_path)

def preprocess_image(img_path, target_size=(32, 32)):
    """Load and preprocess an image."""
    img = image.load_img(img_path, target_size=target_size)
    input_data = image.img_to_array(img)
    input_data = np.expand_dims(input_data, axis=0)  # Add batch dimension
    return input_data

def save_layer_outputs(model, input_data, output_dir="layer_outputs"):
    """Save each layer's output to a file."""
    # Ensure the output directory exists
    os.makedirs(output_dir, exist_ok=True)

    # Get outputs for all layers
    layer_outputs = [layer.output for layer in model.layers]
    intermediate_model = tf.keras.models.Model(inputs=model.inputs, outputs=layer_outputs)
    outputs = intermediate_model.predict(input_data)

    for i, output in enumerate(outputs):
        layer_name = model.layers[i].name
        file_path = os.path.join(output_dir, f"{layer_name}_output.txt")
        
        # Save the output in the desired format
        with open(file_path, "w") as f:
            if len(output.shape) > 2:  # For layers with multiple dimensions
                # Reshape to 2D for row-wise formatting
                reshaped_output = output[..., 0].squeeze()  # Take the first channel and remove extra dimensions
                for row in reshaped_output:
                    row_str = " ".join([f"{value:.5f}" for value in row])
                    f.write(row_str + "\n")
            else:
                # For 1D outputs
                output_str = " ".join([f"{value:.5f}" for value in output.squeeze()])
                f.write(output_str + "\n")

# Main script
if __name__ == "__main__":
    # Paths
    model_path = "E:/Assignment-2-C++/Project_Root/cifar10_hyperParameter_model.h5"
    img_path = "E:/Assignment-2-C++/Project_Root/selected_image.png"
    output_dir = "layer_outputs"

    # Class names
    class_names = ['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']

    # Load model and preprocess image
    model = load_model(model_path)
    input_data = preprocess_image(img_path)

    # Save layer outputs
    save_layer_outputs(model, input_data, output_dir=output_dir)

    # Get the prediction
    last_layer_output = model.predict(input_data)
    y_pred = np.argmax(last_layer_output, axis=1)

    # Print the final predicted class
    print(f"Predicted class: {class_names[y_pred[0]]}")
