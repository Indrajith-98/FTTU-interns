# ResNet50 v2: Enhanced Image Classification with Advanced Techniques

This project showcases the implementation of a ResNet50 v2 model for image classification, leveraging advanced techniques to enhance performance and training efficiency. The model is trained on the CIFAR-10 dataset and achieves an accuracy of 82%.

## Key Features

- **Hyperparameter Tuning:** Optimize model performance through systematic tuning of hyperparameters.
- **Image Augmentation:** Enhance training data diversity and improve generalization using techniques like rotation, shifts, flips, and zooms.
- **Checkpointing:** Save model weights during training to restore the best-performing model.
- **Early Stopping:** Prevent overfitting by halting training when validation loss stagnates for a set number of epochs.
- **Learning Rate Reduction:** Adjust learning rate dynamically when validation loss plateaus to aid model convergence.
- **TensorRT Optimization:** Convert the trained TensorFlow model to a TensorRT engine for superior inference performance.

## Project Structure

- **`Resnet50.ipynb`:** This Jupyter Notebook includes:
  - Loading and preprocessing the CIFAR-10 dataset.
  - Building and training the ResNet50 v2 model using Keras.
  - Implementing image augmentation, checkpointing, early stopping, and learning rate reduction.
  - Saving the trained model in TensorFlow SavedModel format.
  - Converting the TensorFlow model to ONNX format.
  - Transforming the ONNX model into a TensorRT engine.
- **`inference.py`:** This Python script is responsible for:
  - Loading the TensorRT engine.
  - Benchmarking the inference speed and throughput of the TensorRT engine.

## Dependencies

- **TensorFlow**
- **Keras**
- **TensorRT**
- **PyCUDA**
- **ONNX**
- **tf2onnx**

## Usage

1. **Training:** Execute the `Resnet50.ipynb` notebook to train the model and generate the TensorRT engine.
2. **Inference:** Run the `inference.py` script to evaluate the inference speed and throughput of the TensorRT engine.

## Performance

The TensorRT engine delivers the following performance metrics on an RTX 2050 Mobile:

- **Average Inference Time:** 2.07 ms
- **Throughput:** 480.49 images/second

These results highlight the substantial performance improvements achieved with TensorRT optimization for inference.
