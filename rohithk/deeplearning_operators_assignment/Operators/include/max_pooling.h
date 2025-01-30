#ifndef MAX_POOLING_H
#define MAX_POOLING_H

#include <ctensor.h>
#include <ctypes.h>
#include <iostream>
using namespace std;

CImage max_pooling(const CImage &image, int kernel_size, int stride,
                   int padding);
#endif