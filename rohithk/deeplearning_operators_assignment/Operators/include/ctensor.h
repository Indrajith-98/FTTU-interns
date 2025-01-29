#ifndef CTENSOR_H
#define CTENSOR_H

#include <iostream>
#include <vector>

class CTensor {
public:
  std::vector<int> shape;
  std::vector<float> data;

  CTensor();
  CTensor(const std::vector<int> &shape_, float val = 0.0);
  CTensor(const CTensor &copy);
};

#endif
