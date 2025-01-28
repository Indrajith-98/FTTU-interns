#include "my_math.h"
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

int MyMath::factorial(int n) {
  if (n < 0) {
    throw std::invalid_argument("Factorial is not defined for negative numbers.");
  }
  if (n > 12) {  // Factorials larger than 12! will overflow an int
    throw std::overflow_error("Factorial result exceeds int limits.");
  }
  if (n == 0) {
    return 1;
  } else {
    return n * factorial(n - 1);
  }
}

int MyMath::fibonacci(int n) {
  if (n < 0) {
    throw std::invalid_argument("Fibonacci is not defined for negative numbers.");
  }
  if (n > 45) {  // Fibonacci(46) exceeds int limits
    throw std::overflow_error("Fibonacci result exceeds int limits.");
  }
  if (n <= 1) {
    return n;
  } else {
    return fibonacci(n - 1) + fibonacci(n - 2);
  }
}

#include <stdexcept>
#include <limits>

int MyMath::gcd(int a, int b) {
  // Check for overflow in the input values
  if (a < 0 || b < 0) {
    throw std::invalid_argument("GCD is not defined for negative numbers.");
  }
  if (a > 2147483647 || b > 2147483647) {
    throw std::overflow_error("Input values for GCD exceed int limits.");
  }
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

int MyMath::lcm(int a, int b) {
  // Check for overflow in the input values
  if (a < 0 || b < 0) {
    throw std::invalid_argument("LCM is not defined for negative numbers.");
  }
  if (a == 0 || b == 0) {
    return 0;
  } else {
    // Check if a * b would overflow
    if (static_cast<long long>(a) * b > std::numeric_limits<int>::max()) {
      throw std::overflow_error("LCM result exceeds int limits.");
    }
    long long result = static_cast<long long>(a) * b / gcd(a, b);
    return static_cast<int>(result);
  }
}

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
  return factors;
}

double MyMath::calculate_pi(int num_iterations) {
  if (num_iterations <= 0) {
    throw std::invalid_argument("Number of iterations must be greater than 0.");
  }
  if (num_iterations > 1000000) {  // Artificial limit for iterations to prevent excessive computation
    throw std::overflow_error("Too many iterations for Pi calculation.");
  }
  double sum = 0.0;
  for (int i = 0; i < num_iterations; ++i) {
    double term = pow(-1, i) / (2 * i + 1);
    sum += term;
  }
  return 4 * sum;
}

double MyMath::sigmoid(double x) {
  if (x > 100) {
    return 1.0;  // Prevent overflow in exp
  }
  if (x < -100) {
    return 0.0;  // Prevent underflow in exp
  }
  return 1.0 / (1.0 + exp(-x));
}

double MyMath::relu(double x) {
  return std::max(0.0, x);
}



double MyMath::mean_squared_error(const std::vector<double>& y_true,
                                  const std::vector<double>& y_pred) {
  if (y_true.size() != y_pred.size()) {
    throw std::invalid_argument("y_true and y_pred must have the same size.");
  }

  double sum_squared_errors = 0.0;
  for (size_t i = 0; i < y_true.size(); ++i) {
    double error = y_true[i] - y_pred[i];
    sum_squared_errors += error * error;
  }

  return sum_squared_errors / y_true.size();
}
