import tvm
from tvm.ir.transform import Sequential
from tvm.relay import transform
from scripts.logger import get_logger
from tvm.ir import save_json


logger = get_logger("OptimizeModel")


def optimize_model(mod):
    logger.info("Applying optimization passes...")

    passes = Sequential(
        [
            transform.SimplifyInference(),
            transform.FoldConstant(),
            transform.FoldScaleAxis(),
            transform.FuseOps(),
        ]
    )

    with tvm.transform.PassContext(opt_level=1):
        mod = passes(mod)

    logger.info("Optimization passes applied.")

    with open("relay_ir.txt", "w") as f:
        f.write(str(mod))
    logger.info("Relay IR saved to relay_ir.txt")
    with open("relay_ir.json", "w") as fl:
        fl.write(save_json(mod))
    logger.info("Relay IR saved to relay_ir.json")

    return mod
