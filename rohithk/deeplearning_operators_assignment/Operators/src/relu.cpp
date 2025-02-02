#include <relu.h>
using namespace std;

CTensor relu(CTensor input) {
  CTensor output;
  output.shape = input.shape;
  output.data = input.data;
  for (size_t i = 0; i < input.data.size(); i++) {
    output.data[i] = max((double)0.0, input.data[i]);
  }
  return output;
}