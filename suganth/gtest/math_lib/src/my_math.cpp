#include "my_math.h"
#include <cmath>
#include <limits>
#include <stdexcept>

// Factorial: Handles integer overflow
int MyMath::factorial(int n) {
  if (n < 0) {
    throw std::invalid_argument("Factorial is not defined for negative numbers.");
  }
  int result = 1;
  for (int i = 2; i <= n; ++i) {
    if (result > std::numeric_limits<int>::max() / i) {
      throw std::overflow_error("Factorial result exceeds the maximum value for int.");
    }
    result *= i;
  }
  return result;
}

// Fibonacci: Handles integer overflow
int MyMath::fibonacci(int n) {
  if (n < 0) {
    throw std::invalid_argument("Fibonacci is not defined for negative numbers.");
  }
  if (n <= 1) {
    return n;
  }
  int a = 0, b = 1;
  for (int i = 2; i <= n; ++i) {
    if (b > std::numeric_limits<int>::max() - a) {
      throw std::overflow_error("Fibonacci result exceeds the maximum value for int.");
    }
    int temp = a + b;
    a = b;
    b = temp;
  }
  return b;
}

// GCD: No changes, already handles edge cases
int MyMath::gcd(int a, int b) {
  if (a < 0 || b < 0) {
    throw std::invalid_argument("GCD is not defined for negative numbers.");
  }
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// LCM
int MyMath::lcm(int a, int b) {
  if (a < 0 || b < 0) {
    throw std::invalid_argument("LCM is not defined for negative numbers.");
  }
  if (a == 0 || b == 0) {
    return 0;
  } else {
    return (a * b) / gcd(a, b);
  }
}


// Prime Factors: Handles large inputs
std::vector<int> MyMath::prime_factors(int n) {
  if (n <= 1) {
    throw std::invalid_argument("Prime factorization is not defined for numbers less than or equal to 1.");
  }
  std::vector<int> factors;
  for (int i = 2; i * i <= n; ++i) {
    while (n % i == 0) {
      factors.push_back(i);
      n /= i;
    }
  }
  if (n > 1) {
    factors.push_back(n);
  }
  return factors;}

// Pi Calculation: No changes, handles precision via double
double MyMath::calculate_pi(int num_iterations) {
  if (num_iterations <= 0) {
    throw std::invalid_argument("Number of iterations must be greater than 0.");
  }
  double sum = 0.0;
  for (int i = 0; i < num_iterations; ++i) {
    double term = pow(-1, i) / (2 * i + 1);
    sum += term;
  }
  return 4 * sum; 
}

// Sigmoid: Handles input range and avoids floating-point overflow
double MyMath::sigmoid(double x) {
  if (x > 709) { // Avoids exp(x) overflow for large x
    return 1.0;
  } else if (x < -709) { // Avoids exp(x) underflow for small x
    return 0.0;
  }
  return 1.0 / (1.0 + exp(-x));
}

// ReLU: No changes, inherently simple
double MyMath::relu(double x) {
  return std::max(0.0, x);
}

// Mean Squared Error: Handles input size mismatch and floating-point precision
double MyMath::mean_squared_error(const std::vector<double>& y_true,
                                  const std::vector<double>& y_pred) {
  if (y_true.size() != y_pred.size()) {
    throw std::invalid_argument("y_true and y_pred must have the same size.");
  }

  double sum_squared_errors = 0.0;
  for (size_t i = 0; i < y_true.size(); ++i) {
    double error = y_true[i] - y_pred[i];
    sum_squared_errors += error * error;
    if (sum_squared_errors > std::numeric_limits<double>::max()) {
      throw std::overflow_error("Sum of squared errors exceeds the maximum value for double.");
    }
  }

  return sum_squared_errors / y_true.size();
}
