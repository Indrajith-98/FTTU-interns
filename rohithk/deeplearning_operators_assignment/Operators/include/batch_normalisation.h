#ifndef BATCH_NORM_H
#define BATCH_NORM_H

#include <cmath>
#include <vector>

using namespace std;

vector<vector<vector<double>>>
batch_norm(const vector<vector<vector<double>>> &image,
           const vector<double> &gamma, const vector<double> &beta,
           double epsilon);
#endif
