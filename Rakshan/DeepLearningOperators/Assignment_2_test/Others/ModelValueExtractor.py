# import tensorflow as tf
# import numpy as np

# def print_all_channels_outputs(model, input_data):
#     # Output file path
#     output_file_path = "D:/MCW/Assignment-2/Assignment_2_test/MODEL_LAYER_WISE_OUTPUT.txt"
    
#     # Clear the output file before writing
#     open(output_file_path, "w").close()
    
#     # Get outputs of all layers
#     layer_outputs = [layer.output for layer in model.layers]
#     intermediate_model = tf.keras.models.Model(inputs=model.inputs, outputs=layer_outputs)
    
#     # Get outputs for the input data
#     outputs = intermediate_model.predict(input_data)
    
#     for i, output in enumerate(outputs):
#         layer_name = model.layers[i].name
        
#         # Write layer information to the file
#         with open(output_file_path, "a") as file:
#             file.write(f"Layer {i+1} - {layer_name} \n")
        
#         # Loop through all channels in the output
#         if len(output.shape) > 3:  # If the output has more than 3 dimensions (e.g., (batch_size, height, width, channels))
#             for channel in range(output.shape[-1]):  # Loop through all channels
#                 channel_output = output[..., channel]  # Extract output for the current channel
                
#                 with open(output_file_path, "a") as file:
#                     file.write(f"Channel {channel}: \n")
#                     file.write(str(channel_output))
#                     file.write(" \n" + "-" * 50 + " \n")
#         else:
#             # If it's a 1D or 2D output (e.g., in fully connected layers), write the output as is
#             with open(output_file_path, "a") as file:
#                 file.write(str(output))
#                 file.write(" \n" + "-" * 50 + " \n")

# # Load the model
# model = tf.keras.models.load_model('D:/MCW/Assignment-1/DATA_AUG.keras')

# # Dummy input to test the function
# from tensorflow.keras.preprocessing import image

# # Create dummy input data with shape (1, 32, 32, 3) and fill with 1.0
# img_path = "D:/MCW/Assignment-2/resized_image_cifar.jpeg"
# img = image.load_img(img_path, target_size=(32, 32))
# input_data = image.img_to_array(img)
# input_data = np.expand_dims(input_data, axis=0)

# # Call the function
# print_all_channels_outputs(model, input_data)


# ###########################################
# import tensorflow as tf
# import numpy as np
# from tensorflow.keras.utils import load_img, img_to_array

# def print_first_channel_outputs(model, input_data):
#     output_file_path = "D:/MCW/Assignment-2/Assignment_2_test/MODEL_LAYER_WISE_OUTPUT.txt"
    
#     # Clear the output file before writing
#     open(output_file_path, "w").close()
    
#     layer_outputs = [layer.output for layer in model.layers]  
#     intermediate_model = tf.keras.models.Model(inputs=model.inputs, outputs=layer_outputs)
    
#     # Get outputs for the input data
#     outputs = intermediate_model.predict(input_data)
    
#     for i, output in enumerate(outputs):
#         with open(output_file_path, "a") as file:
#             file.write(f"Layer {i+1} - {model.layers[i].name}\n")
#             file.write(f"Output shape: {output.shape}\n")
            
#             np.set_printoptions(threshold=np.inf)  # Ensure the output is not truncated
#             file.write(str(output))  # For 1D or scalar outputs, write as is
#             file.write("\n" + "-" * 50 + "\n")
    
#     return outputs

# model = tf.keras.models.load_model("D:/MCW/Assignment-1/DATA_AUG.keras")

# # Load and preprocess the image
# img_path = "D://MCW//Assignment-2//resized_image_cifar.jpeg"
# img = load_img(img_path, target_size=(32, 32))
# input_data = img_to_array(img)
# input_data = np.expand_dims(input_data, axis=0)
# input_data = input_data / 255.0  # Normalize the input data

# output = print_first_channel_outputs(model, input_data)
# last_layer_output = output[-1]  # Get the last layer's output
# y_pred = np.argmax(last_layer_output, axis=1)  # Get prediction from the last layer's output
# class_names = ['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']
# print(class_names[y_pred[0]])
import tensorflow as tf
import numpy as np
from tensorflow.keras.preprocessing import image

def print_first_channel_outputs(model, input_data):
    output_file_path = "D:/MCW/Assignment-2/Assignment_2_test/MODEL_LAYER_WISE_OUTPUT.txt"
    
    # Clear the output file before writing
    open(output_file_path, "w").close()
    
    layer_outputs = [layer.output for layer in model.layers]  # Get outputs of all layers
    intermediate_model = tf.keras.models.Model(inputs=model.inputs, outputs=layer_outputs)
    
    # Get outputs for the input data
    outputs = intermediate_model.predict(input_data)
    
    for i, output in enumerate(outputs):
        with open(output_file_path, "a") as file:
            file.write(f"Layer {i+1} - {model.layers[i].name}\n")
            if len(output.shape) > 2:  # For layers with multiple channels
                file.write(str(output[..., 0]))  # Write only the first channel
            else:
                file.write(str(output))  # For 1D or scalar outputs, write as is
            file.write("\n" + "-" * 50 + "\n")
    
    return outputs

model = tf.keras.models.load_model("D:/MCW/layerDumpout/DATA_AUG.keras")

# Load and preprocess the image
img_path = "D://MCW//Assignment-2//resized_image_cifar.jpeg"
img = image.load_img(img_path, target_size=(32, 32))
input_data = image.img_to_array(img)
input_data = np.expand_dims(input_data, axis=0)
input_data = input_data / 255.0  # Normalize the input data

output = print_first_channel_outputs(model, input_data)
last_layer_output = output[-1]  # Get the last layer's output
y_pred = np.argmax(last_layer_output, axis=1)  # Get prediction from the last layer's output
class_names = ['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']
print(class_names[y_pred[0]])
