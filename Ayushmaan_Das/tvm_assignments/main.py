from scripts.load_model import load_onnx_model
from scripts.optimize_model import optimize_model
from scripts.compile_model import compile_and_save_model
from scripts.run_inference import run_inference
from scripts.logger import get_logger

logger = get_logger("Main")

# Model path
MODEL_PATH = "models/fashion_mnist.onnx"


def main():
    logger.info("Starting TVM model processing pipeline...")

    # Step 1: Load and Convert Model
    mod, params = load_onnx_model(MODEL_PATH)
    if mod is None:
        logger.error("Failed to load model. Exiting...")
        return

    # Step 2: Optimize Model
    # mod = optimize_model(mod)

    # Step 3: Compile Model
    # lib = compile_and_save_model(mod, params)

    # Step 4: Run Inference
    # run_inference(lib)

    # logger.info("TVM processing pipeline completed successfully!")


if __name__ == "__main__":
    main()
