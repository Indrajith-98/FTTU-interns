import cv2
import numpy as np
import json
from typing import Tuple


class BatchNormalizer:
    def __init__(self, epsilon: float = 1e-5):
        self.epsilon = epsilon
        self.mean = None
        self.variance = None
        self.normalized = None

    def normalize(self, image: np.ndarray) -> np.ndarray:
        """
        Perform batch normalization on an RGB image
        Args:
            image: RGB image of shape (height, width, channels)
        Returns:
            normalized image of same shape
        """
        # Reshape image to (N, D) where N is number of pixels and D is channels
        height, width, channels = image.shape
        reshaped_image = image.reshape(-1, channels)

        # Calculate mean and variance along the pixel dimension
        self.mean = np.mean(reshaped_image, axis=0)
        self.variance = np.var(reshaped_image, axis=0)

        # Normalize
        self.normalized = (reshaped_image - self.mean) / np.sqrt(
            self.variance + self.epsilon
        )

        # Reshape back to original dimensions
        normalized_image = self.normalized.reshape(height, width, channels)

        return normalized_image

    def get_stats(self) -> dict:
        """Return normalization statistics"""
        return {
            "mean": self.mean.tolist() if self.mean is not None else None,
            "variance": self.variance.tolist() if self.variance is not None else None,
            "epsilon": self.epsilon,
        }


def load_and_preprocess_image(image_path: str) -> Tuple[np.ndarray, Tuple[int, int]]:
    """
    Load and preprocess image
    Args:
        image_path: path to image file
    Returns:
        preprocessed image, original shape
    """
    # Load image
    image = cv2.imread(image_path)
    if image is None:
        raise ValueError(f"Could not load image from {image_path}")

    # Convert BGR to RGB
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    # Convert to float32 and scale to [0, 1]
    print(image[0][0])
    return image, image.shape


def save_output_to_json(
    normalized_image: np.ndarray,
    stats: dict,
    original_shape: Tuple[int, int, int],
    output_path: str = "batch_norm_output.json",
):
    """
    Save normalized image and statistics to JSON
    Args:
        normalized_image: normalized image array
        stats: normalization statistics
        original_shape: original image shape
        output_path: path to save JSON file
    """
    output_dict = {
        "metadata": {
            "original_shape": {
                "height": original_shape[0],
                "width": original_shape[1],
                "channels": original_shape[2],
            },
            "normalization_stats": stats,
        },
        "normalized_data": normalized_image.tolist(),
    }

    try:
        with open(output_path, "w") as f:
            json.dump(output_dict, f, indent=2)
        print(f"Successfully saved output to {output_path}")
    except Exception as e:
        print(f"Error saving JSON file: {str(e)}")


def main():
    # Configuration
    image_path = "input_image.png"  # Replace with your image path
    output_path = "batch_norm_output.json"

    try:
        # Load and preprocess image
        print("Loading and preprocessing image...")
        image, original_shape = load_and_preprocess_image(image_path)

        # Perform batch normalization
        print("Performing batch normalization...")
        normalizer = BatchNormalizer()
        normalized_image = normalizer.normalize(image)

        # Get normalization statistics
        stats = normalizer.get_stats()

        # Save results
        print("Saving results...")
        save_output_to_json(normalized_image, stats, original_shape, output_path)

        # Optionally save normalized image for visualization
        # Convert back to uint8 format for saving
        visualization = (
            (normalized_image - normalized_image.min())
            * 255
            / (normalized_image.max() - normalized_image.min())
        ).astype(np.uint8)
        visualization = cv2.cvtColor(visualization, cv2.COLOR_RGB2BGR)
        cv2.imwrite("normalized_image.jpg", visualization)

        print("Batch normalization completed successfully!")
        print(f"Original image shape: {original_shape}")
        print("Normalization statistics:", stats)

    except Exception as e:
        print(f"Error occurred: {str(e)}")


if __name__ == "__main__":
    main()
