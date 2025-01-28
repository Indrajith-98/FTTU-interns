import tensorflow as tf
import numpy as np
from tensorflow.keras.preprocessing import image
import matplotlib.pyplot as plt

def classify_image(model, img_path):
    # Step 1: Load and preprocess the image
    img = image.load_img(img_path, target_size=(32, 32))  # CIFAR-10 images are 32x32
    img_array = image.img_to_array(img)  # Convert the image to a NumPy array
    img_array = np.expand_dims(img_array, axis=0)  # Add batch dimension (for a single image)
    img_array = img_array / 255.0  # Normalize the image (optional, depending on the model)

    # Step 2: Predict class probabilities
    predictions = model.predict(img_array)  # Get model's predicted class probabilities

    # Step 3: Print the predicted class probabilities
    class_probs = predictions[0]  # Since we're predicting for a single image
    for i, prob in enumerate(class_probs):
        print(f"Class {i}: {prob:.4f}")

    # Optionally: Display the image
    plt.imshow(img)
    plt.show()

# Example usage:
# Load your pretrained model (e.g., CIFAR-10 model or any custom model you have)
model = tf.keras.models.load_model('D:/MCW/Assignment-1/DATA_AUG.keras')  # Load the model properly

# Path to your image
img_path = "D:/MCW/Assignment-2/resized_image_cifar.jpeg"  # Replace with the path to your image

# Classify and print class probabilities
classify_image(model, img_path)
