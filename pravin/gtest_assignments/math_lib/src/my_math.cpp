#include "my_math.h"
#include <cmath>
#include <iostream>

int MyMath::factorial(int n) {
  if (n < 0) {
    throw std::invalid_argument("Factorial is not defined for negative numbers.");
  }
  if (n == 0) {
    return 1;
  } else {
    int prev_result = factorial(n - 1);
    if (prev_result > std::numeric_limits<int>::max() / n) {
      throw std::overflow_error("Factorial result exceeds integer limits.");
    }
    return n * prev_result;
  }
}



int MyMath::fibonacci(int n) {
  if (n < 0) {
    throw std::invalid_argument("Fibonacci is not defined for negative numbers.");
  }
  
  if (n <= 1) {
    return n;
  }

  // Use a bottom-up approach to avoid deep recursion
  int a = 0, b = 1;
  
  for (int i = 2; i <= n; ++i) {
    // Check for overflow before performing the addition
    if (b > std::numeric_limits<int>::max() - a) {
      throw std::overflow_error("Fibonacci calculation exceeded integer limit.");
    }
    int next = a + b;
    a = b;
    b = next;
  }

  return b;
}


int MyMath::gcd(int a, int b) {
  if (a < 0 || b < 0) {
    throw std::invalid_argument("GCD is not defined for negative numbers.");
  }
  if (a == 0 && b == 0) {
    throw std::invalid_argument("GCD is not defined for 0 and 0.");
  }

  if (b == 0) {
    return a;
  } 
  else if (a == 0) {
    return b;
  }
  else {
    return gcd(b, a % b);
  }
}


int MyMath::lcm(int a, int b) {
  if (a < 0 || b < 0) {
    throw std::invalid_argument("LCM is not defined for negative numbers.");
  }
  else if (a == 0 && b == 0) {
    throw std::invalid_argument("LCM is not defined for 0 and 0.");
  }
  // Check for overflow before multiplication
  else if (a > std::numeric_limits<int>::max() / b) {
    throw std::overflow_error("LCM calculation would overflow.");
  }
  std::cout << "a: " << a << ", b: " << b << std::endl;
  int c = (a * b) / gcd(a, b);
  std::cout << "c: " << c << std::endl;
  return c;
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

  // Set a reasonable limit for iterations to prevent excessive calculations
  const int MAX_ITERATIONS = 1000000; // Arbitrary large limit, you can adjust this value
  if (num_iterations > MAX_ITERATIONS) {
    throw std::invalid_argument("Number of iterations exceeds the allowed limit.");
  }

  double sum = 0.0;
  for (int i = 0; i < num_iterations; ++i) {
    double term = pow(-1, i) / (2 * i + 1);
    sum += term;
  }

  return 4 * sum; 
}


double MyMath::sigmoid(double x) {
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
  if (y_true.empty() || y_pred.empty()) {
    throw std::invalid_argument("Input vectors are empty.");
  }

  double sum_squared_errors = 0.0;
  for (size_t i = 0; i < y_true.size(); ++i) {
    double error = y_true[i] - y_pred[i];
    sum_squared_errors += error * error;
  }

  return sum_squared_errors / y_true.size();
}
