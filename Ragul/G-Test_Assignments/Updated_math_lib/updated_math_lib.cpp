#include "my_math.h"
#include<cmath>
using namespace std;
// Factorial implementation
int MyMath::factorial(int n) {
    if (n < 0) throw std::invalid_argument("Factorial is not defined for negative numbers.");
    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
        if (result > INT_MAX) throw std::overflow_error("Factorial result exceeds INT_MAX.");
    }
    return static_cast<int>(result);
}

// Fibonacci implementation
int MyMath::fibonacci(int n) {
    if (n < 0) throw std::invalid_argument("Fibonacci is not defined for negative numbers.");
    if (n == 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1, c = 0;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

// GCD implementation
int MyMath::gcd(int a, int b) {
    if (a < 0 || b < 0) throw std::invalid_argument("GCD is not defined for negative numbers.");
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// LCM implementation
int MyMath::lcm(int a, int b) {
    if (a < 0 || b < 0) throw std::invalid_argument("LCM is not defined for negative numbers.");
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

// Prime factors implementation
std::vector<int> MyMath::prime_factors(int n) {
    if (n <= 1) throw std::invalid_argument("Prime factorization is not defined for numbers <= 1.");
    std::vector<int> factors;
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 2) factors.push_back(n);
    return factors;
}

// Calculate PI implementation
double MyMath::calculate_pi(int iterations) {
    if (iterations <= 0) throw std::invalid_argument("Number of iterations must be positive.");
    double pi = 0.0;
    for (int i = 0; i < iterations; ++i) {
        double term = (i % 2 == 0 ? 1.0 : -1.0) / (2.0 * i + 1.0);
        pi += term;
    }
    return pi * 4.0;
}

// Sigmoid implementation
double MyMath::sigmoid(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

// ReLU implementation
double MyMath::relu(double x) {
    return std::max(0.0, x);
}

// Mean Squared Error implementation
double MyMath::mean_squared_error(const std::vector<double>& y_true, const std::vector<double>& y_pred) {
    if (y_true.size() != y_pred.size()) {
        throw std::invalid_argument("Vectors must have the same size.");
    }
    double sum_squared_error = 0.0;
    for (size_t i = 0; i < y_true.size(); ++i) {
        double diff = y_true[i] - y_pred[i];
        sum_squared_error += diff * diff;
    }
    return sum_squared_error / y_true.size();
}
