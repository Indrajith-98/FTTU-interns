import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

# Load CIFAR-10 dataset
(x_train, y_train), (x_test, y_test) = tf.keras.datasets.cifar10.load_data()

# Select the image (e.g., index 11211)
image = x_train[3451]
plt.imshow(image)
plt.show()
# Resize the image to shape (1, 32, 32, 3)
resized_image = np.expand_dims(image, axis=0)
# Normalize the image
resized_image = resized_image / 255.0

# Convert the resized image to binary format and save it
output_file_path = "D:/MCW/Assignment-2/resized_image_binary.bin"
resized_image.astype(np.float32).tofile(output_file_path)
#1237(r),1238(r) 
print(f"Image saved to binary format at {output_file_path}")
# Save the image in JPEG format
jpeg_output_file_path = "D:/MCW/Assignment-2/resized_image_cifar.jpeg"
plt.imsave(jpeg_output_file_path, image)
print(f"Image saved in JPEG format at {jpeg_output_file_path}")