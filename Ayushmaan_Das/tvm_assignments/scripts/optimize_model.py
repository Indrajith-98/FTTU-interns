import tvm
from tvm.ir.transform import Sequential
from tvm.relay import transform
from scripts.logger import get_logger

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

    with tvm.transform.PassContext(opt_level=3):
        mod = passes(mod)

    logger.info("Optimization passes applied.")

    with open("relay_ir.txt", "w") as f:
        f.write(str(mod))
    logger.info("Relay IR saved to relay_ir.txt")

    return mod
