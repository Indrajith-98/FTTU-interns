import tensorflow as tf
import numpy as np
import json

# Load JSON configuration
config_file_path = "../configs/config_file.json"
with open(config_file_path, "r") as json_file:
    config = json.load(json_file)

# Access layers array from config
layers = config["layers"]

# Base path for weights
base_path = "../"

# Initialize a shared variable for layer outputs
layer_output = None


def save_first_channel(layer_output, layer_name):
    with open("../data/python_outputs/" + layer_name + "_output" + ".txt", "a") as file:
        if (
            len(layer_output.shape) > 3
        ):  # If output has more than one channel (e.g., 4D tensor)
            np.savetxt(file, layer_output[0, :, :, 0], fmt="%.6f")
        else:
            np.savetxt(file, layer_output, fmt="%.6f")
        file.write("\n")


def batch_normalization(layer_output):
    weights_file_paths = layer["weights_file_paths"]
    assert (
        len(weights_file_paths) == 4
    ), "Invalid number of weight paths in the configuration file for batch_normalization layer"

    gamma_path = base_path + weights_file_paths[0]
    beta_path = base_path + weights_file_paths[1]
    moving_mean_path = base_path + weights_file_paths[2]
    moving_variance_path = base_path + weights_file_paths[3]

    output_channels = layer["attributes"]["output_shape"][3]

    gamma = np.fromfile(gamma_path, dtype=np.float32)
    beta = np.fromfile(beta_path, dtype=np.float32)
    moving_mean = np.fromfile(moving_mean_path, dtype=np.float32)
    moving_variance = np.fromfile(moving_variance_path, dtype=np.float32)
    epsilon = 1e-5  # Small constant to avoid division by zero

    layer_output = tf.nn.batch_normalization(
        x=layer_output,
        mean=moving_mean,
        variance=moving_variance,
        offset=beta,
        scale=gamma,
        variance_epsilon=epsilon,
    )

    layer_output = tf.nn.relu(layer_output)

    layer_output = layer_output.numpy()

    save_first_channel(layer_output, layer["layer_name"])

    return layer_output


def batch_normalization1d(layer_output):
    if layer_output is None:
        raise ValueError("layer_output is None before batch normalization 1D.")

    weights_file_paths = layer["weights_file_paths"]
    assert (
        len(weights_file_paths) == 4
    ), "Invalid number of weight paths in the configuration file for batch_normalization layer"

    gamma_path = base_path + weights_file_paths[0]
    beta_path = base_path + weights_file_paths[1]
    moving_mean_path = base_path + weights_file_paths[2]
    moving_variance_path = base_path + weights_file_paths[3]

    # Load weights for batch normalization
    gamma = np.fromfile(gamma_path, dtype=np.float32)
    beta = np.fromfile(beta_path, dtype=np.float32)
    moving_mean = np.fromfile(moving_mean_path, dtype=np.float32)
    moving_variance = np.fromfile(moving_variance_path, dtype=np.float32)
    epsilon = 1e-5  # Small constant to avoid division by zero

    # Perform Batch Normalization for 1D output 
    layer_output = tf.nn.batch_normalization(
        x=layer_output,  # Input tensor of shape [batch_size, 256]
        mean=moving_mean,  # Moving mean (shape: [256])
        variance=moving_variance,  # Moving variance (shape: [256])
        offset=beta,  # Beta parameter (shape: [256])
        scale=gamma,  # Gamma parameter (shape: [256])
        variance_epsilon=epsilon,
    )

    layer_output = tf.nn.relu(layer_output)

    layer_output = layer_output.numpy()

    save_first_channel(layer_output, layer["layer_name"])

    return layer_output


def convolution(layer_output):
    weights_file_paths = layer["weights_file_paths"]
    assert (
        len(weights_file_paths) == 2
    ), "Invalid number of weight paths in the configuration file for conv2d layer"

    kernel_path = base_path + weights_file_paths[0]
    bias_path = base_path + weights_file_paths[1]

    input_height = layer["attributes"]["input_shape"][1]
    input_width = layer["attributes"]["input_shape"][2]
    input_channels = layer["attributes"]["input_shape"][3]
    if layer_output is None:
        layer_output = np.ones(
            (1, input_height, input_width, input_channels), dtype=np.float32
        ) 

    kernel_height = layer["attributes"]["kernel_size"][0]
    kernel_width = layer["attributes"]["kernel_size"][1]
    output_channels = layer["attributes"]["output_shape"][3]

    kernels_flat = np.fromfile(kernel_path, dtype=np.float32)
    biases = np.fromfile(bias_path, dtype=np.float32)

    kernels = kernels_flat.reshape(
        (kernel_height, kernel_width, input_channels, output_channels)
    )

    strides = layer["attributes"]["strides"]
    padding = layer["attributes"]["padding"].upper()

    conv2d_output = tf.nn.conv2d(
        input=layer_output,
        filters=kernels,
        strides=[1, strides[0], strides[1], 1],
        padding=padding,
    )

    conv2d_output = tf.nn.bias_add(conv2d_output, biases)

    layer_output = conv2d_output.numpy()

    save_first_channel(layer_output, layer["layer_name"])

    return layer_output


def max_pooling(layer_output):
    strides = layer["attributes"]["strides"]
    padding = layer["attributes"]["padding"].upper()

    pool_size = [2, 2]  

    maxpooling_output = tf.nn.max_pool2d(
        input=layer_output,
        ksize=[1, pool_size[0], pool_size[1], 1],
        strides=[1, strides[0], strides[1], 1],
        padding=padding,
    )

    layer_output = maxpooling_output.numpy()

    save_first_channel(layer_output, layer["layer_name"])

    return layer_output


def dense(layer_output):
    weights_file_paths = layer["weights_file_paths"]
    assert (
        len(weights_file_paths) == 2
    ), "Invalid number of weight paths in the configuration file for dense layer"

    weights_path = base_path + weights_file_paths[0]
    bias_path = base_path + weights_file_paths[1]
    # Load weights and biases
    weights = np.fromfile(weights_path, dtype=np.float32)
    biases = np.fromfile(bias_path, dtype=np.float32)

    input_size = layer["attributes"]["input_shape"][1]
    output_size = layer["attributes"]["output_shape"][1]

    weights = weights.reshape((input_size, output_size))

    # Flatten the input if necessary
    if len(layer_output.shape) > 2:
        layer_output = layer_output.reshape((layer_output.shape[0], -1))

    dense_output = tf.matmul(layer_output, weights) + biases

    activation = layer["attributes"]["activation"]
    if activation == "relu":
        dense_output = tf.nn.relu(dense_output)
    elif activation == "softmax":
        dense_output = tf.nn.softmax(dense_output)
    else:
        pass

    layer_output = dense_output.numpy()

    save_first_channel(layer_output, layer["layer_name"])

    return layer_output


for layer in layers:
    if "conv" in  layer["layer_name"] :
        layer_output = convolution(layer_output)

    elif layer["layer_name"] == "batch_normalization":
        layer_output = batch_normalization(layer_output)

    elif "max_pooling" in layer["layer_name"] :
        layer_output = max_pooling(layer_output)

    elif layer["layer_name"] == "batch_normalization_1":
        layer_output = batch_normalization(layer_output)

    elif layer["layer_name"] == "batch_normalization_2":
        layer_output = batch_normalization(layer_output)

    elif "dense" in layer["layer_name"] :
        layer_output = dense(layer_output)

    elif layer["layer_name"] == "batch_normalization_3":
        layer_output = batch_normalization1d(layer_output)
