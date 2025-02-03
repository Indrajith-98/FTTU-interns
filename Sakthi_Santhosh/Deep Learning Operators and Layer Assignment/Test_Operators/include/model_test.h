#ifndef MODEL_TEST_H
#define MODEL_TEST_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

const std::vector<std::string> class_names = {"airplane", "automobile", "bird", "cat", "deer", "dog", "frog", "horse", "ship", "truck"};

// Parses a line from a file into a vector of floats
std::vector<float> parseLine(const std::string &line);

// Retrieves the indices of the largest values in each line of the file
std::vector<int> getLargestValueIndices(const std::string &filename);

// Compares the largest value indices from two files
bool compareResults(const std::vector<int> &result1, const std::vector<int> &result2);

#endif // MODEL_TEST_H
