#ifndef CTENSOR_H
#define CTENSOR_H

#include <iostream>
#include <vector>

class CTensor {
public:
  std::vector<int> shape;
  std::vector<double> data;

  CTensor();
  CTensor(const std::vector<int> &shape_, double val = 0.0);
  CTensor(const CTensor &copy);
};

#endif
