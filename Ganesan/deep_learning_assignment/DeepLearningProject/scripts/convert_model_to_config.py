import json
import os

# Get absolute path to model.json
script_dir = os.path.dirname(os.path.abspath(__file__))
model_path = os.path.abspath(os.path.join(script_dir, "../configs/json/model.json"))
config_path = os.path.abspath(os.path.join(script_dir, "../configs/json/config.json"))

print(f"🔍 Checking model.json at: {model_path}")

def extract_config(json_file, output_file):
    # Debugging: Check if the file exists before opening
    if not os.path.exists(json_file):
        print(f"❌ ERROR: {json_file} does not exist!")
        return

    with open(json_file, "r") as f:
        model_data = json.load(f)

    layers = []
    for node in model_data["graph"]["node"]:
        layer = {
            "name": node["name"],
            "type": node["opType"],
            "input": node["input"],
            "output": node["output"],
            "attributes": {attr["name"]: attr["ints"] if "ints" in attr else attr["i"] for attr in node.get("attribute", [])}
        }
        layers.append(layer)

    config = {"layers": layers, "test_type": "model"}

    with open(output_file, "w") as f:
        json.dump(config, f, indent=4)

    print(f"✅ Successfully created config.json at: {output_file}")

# Use absolute paths
extract_config(model_path, config_path)
