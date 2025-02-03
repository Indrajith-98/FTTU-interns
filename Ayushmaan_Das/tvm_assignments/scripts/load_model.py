import onnx
import tvm
from tvm import relay
from scripts.logger import get_logger

logger = get_logger("LoadModel")


def load_onnx_model(model_path, input_name="inputs", input_shape=(1, 1, 28, 28)):
    logger.info(f"Loading ONNX model from {model_path}")

    try:
        onnx_model = onnx.load(model_path)
        logger.info("Successfully loaded ONNX model.")
    except Exception as e:
        logger.error(f"Failed to load ONNX model: {e}")
        return None, None

    shape_dict = {input_name: input_shape}
    logger.info("Converting ONNX model to TVM Relay format...")

    try:
        mod, params = relay.frontend.from_onnx(onnx_model, shape_dict)
        logger.info("Successfully converted ONNX model to TVM Relay format.")
        return mod, params
    except Exception as e:
        logger.error(f"Conversion failed: {e}")
        return None, None
