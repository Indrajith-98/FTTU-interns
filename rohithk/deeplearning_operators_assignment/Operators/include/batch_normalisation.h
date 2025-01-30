#ifndef BATCH_NORM_H
#define BATCH_NORM_H

#include <cmath>
#include <vector>

using namespace std;

vector<vector<vector<float>>>
batch_norm(const vector<vector<vector<float>>> &image,
           const vector<float> &gamma, const vector<float> &beta,
           float epsilon = 1e-5);

#endif
