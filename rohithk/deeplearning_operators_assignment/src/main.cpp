#include <batch_normalisation.h>
#include <conv2d.h>
#include <ctypes.h>
#include <max_pooling.h>
#include <utils.h>
using namespace std;
int main() {
  CTensor tensor;
  tensor.shape = {1, 3, 3, 3};
  tensor.data = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
                 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};
  // CTensor kernel;
  // kernel.shape = {1, 3, 2, 2};
  // kernel.data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  vector<float> gamma = {1.0f, 1.0f, 1.0f}; // Scaling factor (set to 1 for now)
  vector<float> beta = {0.0f, 0.0f, 0.0f};
  // CImage image_ = Utils::deflattenTensor(kernel);

  // Conv2D conv2d(3, 1, 2, 1, 0, kernel, tensor);
  // conv2d.performConvOp(tensor);
  CImage temp = Utils::deflattenTensor(tensor);
  // temp = batch_norm(temp, gamma, beta);
  // Utils::printCImage(temp);
  int kernel_size = 2;
  int stride = 2;
  int padding = (temp[0].size() % kernel_size != 0) ? 1 : 0;

  vector<vector<vector<float>>> output =
      max_pooling(temp, kernel_size, stride, padding);

  cout << "Max Pooled Output:" << endl;
  for (int c = 0; c < output.size(); ++c) {
    cout << "Channel " << c << ":" << endl;
    for (int h = 0; h < output[0].size(); ++h) {
      for (int w = 0; w < output[0][0].size(); ++w) {
        cout << output[c][h][w] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}
// 1 2 3  10 11 12  19 20 21
// 4 5 6  13 14 15  22 23 24
// 7 8 9  16 17 18  25 26 27