import numpy as np
import os
import glob

# Reference directory containing CIFAR-10 outputs
reference_dir = "../data/reference"

# Get all `.bin` files inside the directory
reference_files = sorted(glob.glob(os.path.join(reference_dir, "*.bin")))

if not reference_files:
    print("ERROR: No reference files found in ./data/reference")
    exit(1)

for reference_file in reference_files:
    try:
        # Load binary file
        full_output = np.fromfile(reference_file, dtype=np.float32)

        # Extract filename (e.g., "cifar_output_1.bin")
        file_name = os.path.basename(reference_file)
        file_index = file_name.split("_")[-1].split(".")[0]  # Extract number from filename

        # Define split sizes (Modify these based on your architecture)
        conv_size = 32 * 32
        relu_size = conv_size
        softmax_size = 10

        # Extract layer-wise outputs
        conv_output = full_output[:conv_size]
        relu_output = full_output[conv_size:conv_size + relu_size]
        softmax_output = full_output[-softmax_size:]

        # Output directory for extracted reference files
        output_dir = "./data/reference/layer_outputs"
        os.makedirs(output_dir, exist_ok=True)

        # Save extracted outputs
        conv_output.tofile(os.path.join(output_dir, f"conv_test_output_{file_index}.bin"))
        relu_output.tofile(os.path.join(output_dir, f"relu_test_output_{file_index}.bin"))
        softmax_output.tofile(os.path.join(output_dir, f"softmax_test_output_{file_index}.bin"))

        print(f"Extracted outputs from {file_name} -> Saved layer-wise reference outputs!")

    except Exception as e:
        print(f" ERROR processing {reference_file}: {e}")

print("All layer-wise reference outputs generated successfully!")
