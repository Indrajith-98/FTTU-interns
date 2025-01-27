import numpy as np
import tvm
import onnx
from tvm import relay, relax
from tvm.contrib import graph_executor
import cv2

# Load the ONNX model
onnx_model_path = "cnn_model.onnx"  # Your ONNX model
onnx_model = onnx.load(onnx_model_path)

# Define the input name and shape
input_name = "args_0"  # Ensure this matches the input name in your ONNX model
input_shape = (1, 32, 32, 3)  # Batch size 1, height 32, width 32, channels 3
shape_dict = {input_name: input_shape}

# Convert the ONNX model to TVM Relay format
mod, params = relay.frontend.from_onnx(onnx_model, shape_dict)

# Preprocess the input image
image_path = "img2.jpg"  # Path to your input image
image = cv2.imread(image_path)  # Load the image
image = cv2.resize(image, (32, 32))  # Resize to (32, 32)
image = image.astype("float32") / 255.0  # Normalize pixel values to [0, 1]
image = np.expand_dims(image, axis=0)  # Add batch dimension (1, 32, 32, 3)

# Compile the model for the LLVM target
target = tvm.target.Target("llvm")
with tvm.transform.PassContext(opt_level=3):
    lib = relay.build(mod, target=target, params=params)

# Run the model using TVM Runtime
dev = tvm.cpu(0)
module = graph_executor.GraphModule(lib["default"](dev))
module.set_input(input_name, image)  # Set the preprocessed image as input

# Run the model
module.run()

# Get the output
output = module.get_output(0).numpy()
print("Model output:", output)

# Step 10: Interpret the prediction
class_names = ['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']
predicted_class = np.argmax(output)
print(f"Predicted class: {class_names[predicted_class]}")

# Visualize and Save the Model Before and After Transformation
with open("model_before_transformation_2.json", "w") as f:
    f.write(tvm.ir.save_json(mod))

with open("model_after_transformation_2.json", "w") as f:
    f.write(tvm.ir.save_json(relay.optimize(mod, target, params)))
