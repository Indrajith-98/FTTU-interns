// my_math.h
#ifndef MY_MATH_H
#define MY_MATH_H

#include <vector>
#include <stdexcept>
#include <random>

class MyMath {
 public:
  static int factorial(int n);
  static int fibonacci(int n);
  static int gcd(int a, int b);
  static int lcm(int a, int b);
  static std::vector<int> prime_factors(int n); 
  static double calculate_pi(int num_iterations);

  static double sigmoid(double x);
  static double relu(double x);
  static double mean_squared_error(const std::vector<double>& y_true, 
                                  const std::vector<double>& y_pred);
};

#endif
