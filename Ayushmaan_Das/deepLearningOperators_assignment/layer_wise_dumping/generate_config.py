from onnx2json import convert
import yaml
import json


def onnx_to_json(model_path):
    onnx_json = convert(
        input_onnx_file_path=model_path,
        output_json_path="configs/model_config.json",
        json_indent=2,
    )


def json_to_yaml(model_config_path):
    with open(model_config_path, "r") as json_file:
        json_data = json.load(json_file)

    with open("configs/model_config.yaml", "w") as yaml_file:
        yaml.dump(json_data, yaml_file, default_flow_style=False, indent=2)


if __name__ == "__main__":
    try:
        onnx_to_json("models/hypertuned_resnet34_fashion_mnist.onnx")
        print("Conversion ONNX to JSON successful!")
        try:
            json_to_yaml("configs/model_config.json")
            print("Conversion JSON to YAML successful!")
        except Exception as e:
            print("Error in convert JSON to YAML: ", e)
    except Exception as e:
        print("Error in generate JSON config: ", e)
