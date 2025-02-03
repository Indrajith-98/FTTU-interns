#include <relu.h>
#include <vector>
using namespace std;

vector<vector<vector<double>>> relu(vector<vector<vector<double>>> input) {
  vector<vector<vector<double>>> output = input;
  int height = input.size();
  int width = input[0].size();
  int channels = input[0][0].size();
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      for (int k = 0; k < channels; k++) {
        output[i][j][k] = max((double)0.0, input[i][j][k]);
      }
    }
  }
  return output;
}