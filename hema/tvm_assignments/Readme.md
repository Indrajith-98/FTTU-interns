# Load and Run model using TVM

### Install from source

##### Install Pre-requisite

```
conda env remove -n tvm-build-venv
conda create -n tvm-build-venv -c conda-forge "llvmdev>=15" "cmake>=3.24" git python=3.11
conda activate tvm-build-venv
```

##### Clone TVM repo

```
git clone --recursive https://github.com/apache/tvm tvm
```

##### Build TVM

```
cd tvm
mkdir build
cd build
cmake .. -DUSE_LLVM=ON -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

##### Set up environment variable

```
export TVM_HOME=/d/Tools/tvm
export PYTHONPATH=$TVM_HOME/python:$PYTHONPATH
export LD_LIBRARY_PATH=$TVM_HOME/build/lib:$LD_LIBRARY_PATH
```

##### Create Virtual Env and install library

```
sudo apt install python3-pip

sudo apt install python3-venv
python3 -m venv tvm-venv
source tvm-venv/bin/activate

pip install numpy
pip install decorator
pip install psutil
pip install typing-extensions
pip install attrs
pip install onnx
pip install opencv-python
pip install pillow

```
### Model architecture

```
![modelarch1](image-1.png)
![modelarch2](image.png)
```
### Model output

```
One or more operators have not been tuned. Please tune your model for better performance. Use DEBUG logging level to see more details.
Model output: [[0.08711436 0.13729833 0.09009279 0.10698475 0.09422071 0.09082558
  0.09994613 0.09727602 0.11922817 0.07701316]]
Predicted class: automobile

```