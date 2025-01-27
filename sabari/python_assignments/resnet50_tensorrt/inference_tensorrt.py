import tensorflow as tf
from keras.src.datasets import cifar10
import numpy as np
import tensorrt as trt
import numpy as np
import pycuda.driver as cuda
import pycuda.autoinit 
import time

engine_file = "saved_model.trt"

TRT_LOGGER = trt.Logger(trt.Logger.INFO)

def load_engine(engine_file):
    runtime = trt.Runtime(TRT_LOGGER)
    with open(engine_file, "rb") as f:
        engine_data = f.read()

    # Deserialize the engine
    engine = runtime.deserialize_cuda_engine(engine_data)
    return engine

# Load the engine
engine = load_engine(engine_file)

# Create an execution context
context = engine.create_execution_context()

(train_images, train_labels), (test_images, test_labels) = cifar10.load_data()

num_classes = tf.reduce_max(tf.cast(train_labels, tf.int32)) + 1
train_labels_1h = tf.one_hot( tf.cast(train_labels, tf.int32)[:, 0], depth=num_classes)
test_labels_1h = tf.one_hot( tf.cast(test_labels, tf.int32)[:, 0], depth=num_classes)

test_images_batched = tf.expand_dims(test_images, axis=1).numpy().astype(np.float32)

test_labels_1h_batched = tf.expand_dims(test_labels_1h, axis=1).numpy().astype(np.float32)

# prepare input and output shapes
d_input = cuda.mem_alloc(test_images_batched.nbytes)
d_output = cuda.mem_alloc(test_labels_1h_batched.nbytes)

# memory size of each data point
input_skip_bytes = test_images_batched[0].nbytes
output_skip_bytes = test_labels_1h_batched[0].nbytes

# copy input data to the device memory
cuda.memcpy_htod(d_input, test_images_batched)

def benchmark_inference_time(ctx, num_runs=100):
    start_time = time.time()
    for i in range(num_runs):
        ctx.execute_v2([int(d_input) + i * input_skip_bytes, int(d_output) + i * output_skip_bytes])
    end_time = time.time()
    
    avg_inference_time = (end_time - start_time) / num_runs
    return avg_inference_time

def benchmark_throughput(ctx, total_batches = 10000):
    start_time = time.time()
    for i in range(total_batches):
        ctx.execute_v2([int(d_input) + i * input_skip_bytes, int(d_output) + i * output_skip_bytes])
    end_time = time.time()

    start_time_overhead = time.time()
    for i in range(total_batches):
        pass
    end_time_overhead = time.time()

    total_time = (end_time - start_time) - (end_time_overhead - start_time_overhead)
    throughput = total_batches / total_time

    return throughput

if __name__ == "__main__":
    try:
        # Benchmark inference time
        avg_inference_time = benchmark_inference_time(context, 10000)
        print(f"Average inference time: {avg_inference_time*1000:.2f} ms")

        # Benchmark throughput
        throughput = benchmark_throughput(context, test_images_batched.shape[0])
        print(f"Throughput: {throughput:.2f} images/second")

    except Exception as e:
        print(e)