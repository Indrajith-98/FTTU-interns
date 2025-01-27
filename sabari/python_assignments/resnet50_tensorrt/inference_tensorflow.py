import tensorflow as tf
import time
import numpy as np

# Check for GPU availability
gpus = tf.config.list_physical_devices('GPU')
if gpus:
    print("GPU is available. Using GPU for inference.")
else:
    print("No GPU found. Using CPU for inference.")

# Load the SavedModel
model = tf.saved_model.load('saved_model')

# Check for serving default signature
if 'serving_default' in model.signatures:
    infer = model.signatures['serving_default']
    signature = infer.structured_input_signature
    input_name = list(signature[1].keys())[0] if signature[1] else None
else:
    infer = model
    input_name = None

# Load and preprocess CIFAR-10 data
(_, _), (x_test, _) = tf.keras.datasets.cifar10.load_data()
x_test = x_test.astype('float32') / 255.0

# Create dataset
batch_size = 1
test_dataset = tf.data.Dataset.from_tensor_slices(x_test).batch(batch_size)

# Warm-up run
print("Warming up the model...")
for batch in test_dataset.take(2):
    if input_name:
        infer(**{input_name: batch})
    else:
        infer(batch)

# Performance measurement
total_time = 0.0
total_samples = 0
print("\nMeasuring performance...")

for batch in test_dataset:
    start_time = time.time()
    
    if input_name:
        infer(**{input_name: batch})
    else:
        infer(batch)
        
    elapsed = time.time() - start_time
    total_time += elapsed
    total_samples += batch.shape[0]

# Calculate metrics
average_time_per_sample = total_time / total_samples
throughput = total_samples / total_time

print(f"\nResults:")
print(f"Total samples processed: {total_samples}")
print(f"Total inference time: {total_time:.2f} seconds")
print(f"Average time per sample: {average_time_per_sample:.6f} sec")
print(f"Throughput: {throughput:.2f} samples/sec")