#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "utils.h"
#include "compare_outputs.h"

// Function to perform unit testing of layer outputs
void unit_test();

void model_test();

#endif // UNIT_TEST_H