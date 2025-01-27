# Deep Learning Assignment

### Problem Statement

- **Section 1 :**

  1. Choose a framework (Pytorch or TF) to train a LeNet/ResNet model with a classification dataset
  2. Report the F1 score after training until the training has saturated.
  3. Now tune the hyper parameters and report the new scores after every adjustment.
  4. Try data augmentations and report the scores.
  5. For the best model obtained, get the latency numbers (Time taken for processing a single sample)

- **Section 2 :**
  1. Use TensorRT to accelerate the performance and report the new Latency.

<hr>

### Solution and Links

- The complete **_Google Colab_** notebook can be found [here](https://colab.research.google.com/drive/1FeOQ1VlAKvIbHIEE2Ipjhs-lFGJoiewB?usp=sharing) and also within the repository with the file name [stepwise_implementation.ipynb](stepwise_implementation.ipynb).
- The Output Logs can be found in the [logs](logs/) directory.
- The **ResNet 34** model designed can be found in [resnet34.py](resnet34.py).
- The Model Training codes are as follows:
  - [Initial Training Approach](1_model_training.py).
  - [Training by tuning the hyperparameters](2_hyperparameter_tuning.py).
  - [Training using Augmented Data](3_augmented_training.py)
- The respective model files (`.trt` and `.onnx`) can be found in the repository, but some have not been added to the repo due to large size of the model.

<hr>

### Results

- Comparisions between three versions of the **ResNet 34** Model trained:

| **Model**                                   | **F1 Score** |
| ------------------------------------------- | ------------ |
| **Initial normal training**                 | 0.8928       |
| **Tuned-Hyperparameters Training**          | 0.9160       |
| **Trainig tuned model with Augmented Data** | 0.9126       |

- Results of **TensorRT** Optimization:

| **Metric**                 | **Value**                                                                                         |
| -------------------------- | ------------------------------------------------------------------------------------------------- |
| **Throughput**             | 564.01 qps                                                                                        |
| **Latency**                | Min: 1.75537 ms, Max: 10.467 ms, Mean: 1.80254 ms, Median: 1.77828 ms                             |
|                            | Percentile (90%): 1.81641 ms, Percentile (95%): 1.82147 ms, Percentile (99%): 3.02986 ms          |
| **Enqueue Time**           | Min: 0.183838 ms, Max: 11.081 ms, Mean: 0.268116 ms, Median: 0.266113 ms                          |
|                            | Percentile (90%): 0.312866 ms, Percentile (95%): 0.32373 ms, Percentile (99%): 0.353638 ms        |
| **H2D Latency**            | Min: 0.00610352 ms, Max: 0.0982666 ms, Mean: 0.0308493 ms, Median: 0.0134277 ms                   |
|                            | Percentile (90%): 0.0585938 ms, Percentile (95%): 0.0627441 ms, Percentile (99%): 0.0737305 ms    |
| **GPU Compute Time**       | Min: 1.7431 ms, Max: 10.4111 ms, Mean: 1.76714 ms, Median: 1.74902 ms                             |
|                            | Percentile (90%): 1.75336 ms, Percentile (95%): 1.76129 ms, Percentile (99%): 3.01443 ms          |
| **D2H Latency**            | Min: 0.00341797 ms, Max: 0.0135498 ms, Mean: 0.00455719 ms, Median: 0.00415039 ms                 |
|                            | Percentile (90%): 0.00595093 ms, Percentile (95%): 0.00634766 ms, Percentile (99%): 0.00708008 ms |
| **Total Host Walltime**    | 3.00704 s                                                                                         |
| **Total GPU Compute Time** | 2.99707 s                                                                                         |

<hr>
