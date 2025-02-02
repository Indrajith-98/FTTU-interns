import cv2
import numpy as np
import json


def max_pooling(image, pool_size=2, stride=2):
    """
    Performs max pooling on the input image.

    Parameters:
        image (numpy.ndarray): Input image array (grayscale or color).
        pool_size (int): Size of the pooling window (default is 2).
        stride (int): Stride of the pooling window (default is 2).

    Returns:
        numpy.ndarray: The max pooled image.
    """
    # Get the image dimensions.
    h, w = image.shape[:2]

    # Calculate dimensions for the pooled image.
    new_h = (h - pool_size) // stride + 1
    new_w = (w - pool_size) // stride + 1

    # Initialize the pooled image array depending on image type.
    if len(image.shape) == 3:
        pooled = np.zeros((new_h, new_w, image.shape[2]), dtype=image.dtype)
    else:
        pooled = np.zeros((new_h, new_w), dtype=image.dtype)

    # Slide the window and perform max pooling.
    for i in range(new_h):
        for j in range(new_w):
            window = image[
                i * stride : i * stride + pool_size, j * stride : j * stride + pool_size
            ]
            pooled[i, j] = np.max(window, axis=(0, 1))

    return pooled


# Load the image using OpenCV.
image_path = "input_image.png"  # Replace with your image file path.
image = cv2.imread(image_path)

if image is None:
    raise FileNotFoundError(f"Unable to load image at {image_path}")

# Optional: convert to grayscale if needed.
# image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Apply max pooling with a 2x2 window and stride of 2.
pooled_image = max_pooling(image, pool_size=2, stride=2)

# Convert the numpy array to a list for JSON serialization.
pooled_list = pooled_image.tolist()

# Write the pooled image data to a JSON file.
with open("pooled_output.json", "w") as json_file:
    json.dump(pooled_list, json_file)

# Optionally, display the original and pooled images.
