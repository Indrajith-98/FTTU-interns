import onnx
import numpy as np

model_path = "models/hypertuned_resnet34_fashion_mnist.onnx"
model = onnx.load(model_path)


def print_layer_info(model):
    for layer in model.graph.node:
        print(f"Layer: {layer.name}")
        print(f"  Operator: {layer.op_type}")

        print(f"  Inputs: {layer.input}")
        print(f"  Outputs: {layer.output}")

        for attr in layer.attribute:
            if attr.name == "weights":
                print(f"  Weights: {attr.name} (Shape: {attr.t.dims})")

        for tensor_name in layer.input:
            tensor = next(
                (
                    tensor
                    for tensor in model.graph.value_info
                    if tensor.name == tensor_name
                ),
                None,
            )
            if tensor:
                print(
                    f"  Input Tensor '{tensor_name}' Shape: {tensor.type.tensor_type.shape.dim}"
                )
            else:
                print(f"  Input Tensor '{tensor_name}' Shape: Unknown")

        for tensor_name in layer.output:
            tensor = next(
                (
                    tensor
                    for tensor in model.graph.value_info
                    if tensor.name == tensor_name
                ),
                None,
            )
            if tensor:
                print(
                    f"  Output Tensor '{tensor_name}' Shape: {tensor.type.tensor_type.shape.dim}"
                )
            else:
                print(f"  Output Tensor '{tensor_name}' Shape: Unknown")

        print("=" * 50)


if __name__ == "__main__":
    print_layer_info(model)
