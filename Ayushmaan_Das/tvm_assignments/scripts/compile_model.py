import tvm
from tvm import relay
import os
from scripts.logger import get_logger

logger = get_logger("CompileModel")


def compile_and_save_model(mod, params, target="llvm", model_dir="compiled_tvm_model"):
    logger.info("Compiling the model with LLVM...")

    with tvm.transform.PassContext(opt_level=3):
        lib = relay.build(mod, target=target, params=params)

    logger.info("Compilation successful.")

    # Create directory if not exists
    os.makedirs(model_dir, exist_ok=True)

    # Save compiled artifacts
    lib.export_library(os.path.join(model_dir, "deploy_lib.tar"))

    with open(os.path.join(model_dir, "deploy_graph.json"), "w") as f:
        f.write(lib.get_graph_json())

    with open(os.path.join(model_dir, "deploy_params.params"), "wb") as f:
        f.write(relay.save_param_dict(params))

    logger.info(f"Compiled model saved in {model_dir}")

    return lib
