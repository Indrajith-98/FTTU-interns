from scripts.load_model import load_onnx_model
from scripts.optimize_model import optimize_model
from scripts.compile_model import compile_and_save_model
from scripts.run_inference import run_inference
from scripts.logger import get_logger

logger = get_logger("Main")

MODEL_PATH = "models/hypertuned_resnet34_fashion_mnist.onnx"


def main():
    logger.info("Starting TVM model processing pipeline...")

    mod, params = load_onnx_model(MODEL_PATH)
    if mod is None:
        logger.error("Failed to load model. Exiting...")
        return

    mod = optimize_model(mod)

    lib = compile_and_save_model(mod, params)

    run_inference(lib)

    logger.info("TVM processing pipeline completed successfully!")


if __name__ == "__main__":
    main()
