import numpy as np
import cv2
import os
from tensorflow.keras.models import load_model

# ----------------------------
# Configuration (update as needed)
# ----------------------------
model_path = 'model.h5'      # Path to the Keras .h5 model file
image_path = 'D:/Santhosh@McW/DL_Inference/image.jpg'      # Path to the input image file
output_dir = 'model-output/python'  # Directory to store output files
output_txt_path = os.path.join(output_dir, 'output_probabilities.txt')  # Path to save probabilities
img_width, img_height = 32, 32  # Image size (matching your reference code)

# ----------------------------
# Function to read image as vector
# ----------------------------
def read_image_as_vector(img_path, target_size):
    img = cv2.imread(img_path, cv2.IMREAD_COLOR)
    if img is None:
        raise FileNotFoundError(f"Error: Could not open or find the image: {img_path}")
    
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img = cv2.resize(img, target_size)
    img_vector = img.astype('float32') / 255.0
    return img_vector

# ----------------------------
# Save predictions to text file
# ----------------------------
def save_output_as_txt(probabilities, file_path):
    os.makedirs(output_dir, exist_ok=True)  # Ensure the output directory exists
    with open(file_path, 'w') as f:
        f.write(" ".join([f"{prob:.5f}" for prob in probabilities]))
    print(f"Output saved to {file_path}")

# ----------------------------
# Main workflow
# ----------------------------
def main():
    model = load_model(model_path)
    print(f"Loaded model from {model_path}")

    img_vector = read_image_as_vector(image_path, (img_width, img_height))
    print(f"Loaded and processed image from {image_path}")

    img_vector = np.reshape(img_vector, (1, img_width, img_height, 3))
    predictions = model.predict(img_vector)[0]  # Extract first batch
    print("Prediction completed.")

    save_output_as_txt(predictions, output_txt_path)

if __name__ == '__main__':
    main()
