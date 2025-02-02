#include "ctensor.h"

CTensor::CTensor() : shape(), data() {}

CTensor::CTensor(const std::vector<int> &shape_, double val) : shape(shape_) {
  int size = 1;
  for (int dim : shape)
    size *= dim;
  data = std::vector<double>(size, val);
}

CTensor::CTensor(const CTensor &copy) : shape(copy.shape), data(copy.data) {}
