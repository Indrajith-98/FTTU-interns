#include <conv2d.h>
#include <ctypes.h>
#include <utils.h>
using namespace std;
int main() {
  CTensor tensor;
  tensor.shape = {1, 3, 3, 3};
  tensor.data = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
                 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};
  CTensor kernel;
  kernel.shape = {1, 3, 2, 2};
  kernel.data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  CImage image_ = Utils::deflattenTensor(kernel);

  Conv2D conv2d(3, 1, 2, 1, 0, kernel, tensor);
  conv2d.performConvOp(tensor);

  return 0;
}
// 1 2 3  10 11 12  19 20 21
// 4 5 6  13 14 15  22 23 24
// 7 8 9  16 17 18  25 26 27