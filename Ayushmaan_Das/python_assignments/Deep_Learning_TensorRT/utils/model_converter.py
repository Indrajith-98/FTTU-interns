import tensorflow as tf
from tensorflow.python.framework import convert_to_constants
import tf2onnx

h5_model_path = "hypertuned_resnet34_fashion_mnist.h5"
model = tf.keras.models.load_model(h5_model_path)


def to_savedModelFormat(model=model):
    saved_model_dir = "hypertuned_resnet34_fashion_mnist"
    model.export(saved_model_dir)


def to_pbModelFormat(model=model):
    def save(model, filename):
        full_model = tf.function(lambda x: model(x))
        full_model = full_model.get_concrete_function(
            tf.TensorSpec(model.inputs[0].shape, model.inputs[0].dtype)
        )

        frozen_func = convert_to_constants.convert_variables_to_constants_v2(full_model)
        frozen_graph_def = frozen_func.graph.as_graph_def()

        with tf.io.gfile.GsFile(filename, "wb") as f:
            f.write(frozen_graph_def.SerializeToString())
        print(f"Frozen graph saved to {filename}")

    save(model, filename="hypertuned_resnet34_fashion_mnist.pb")


def to_ONNXformat(model=model):
    tf.saved_model.save(model, "hypertuned_resnet34_fashion_mnist")
    onnx_model = tf2onnx.convert("hypertuned_resnet34_fashion_mnist")
    onnx_model.save("hypertuned_resnet34_fashion_mnist.onnx")
