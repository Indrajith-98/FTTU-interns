import tvm
from tvm.contrib import graph_executor
import numpy as np
import os
from scripts.logger import get_logger

logger = get_logger("RunInference")


def run_inference(
    lib, input_name="inputs", input_shape=(1, 1, 28, 28), model_dir="compiled_tvm_model"
):
    logger.info("Loading the compiled model for execution...")

    dev = tvm.cpu()
    module = graph_executor.GraphModule(lib["default"](dev))

    input_data = np.random.rand(*input_shape).astype("float32")
    module.set_input(input_name, input_data)

    logger.info("Running inference...")
    module.run()

    output = module.get_output(0).asnumpy()
    logger.info(f"Inference completed. Output shape: {output.shape}")

    np.save(os.path.join(model_dir, "output.npy"), output)
    logger.info(f"Output saved as {os.path.join(model_dir, 'output.npy')}")

    return output
