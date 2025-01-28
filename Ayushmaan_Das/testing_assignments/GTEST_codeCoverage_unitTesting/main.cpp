#include <iostream>
#include "my_math.h"

int main()
{
    try
    {
        std::cout << "Factorial of 5: " << MyMath::factorial(5) << std::endl;
        std::cout << "Fibonacci of 5: " << MyMath::fibonacci(5) << std::endl;
        std::cout << "GCD of 48 and 18: " << MyMath::gcd(48, 18) << std::endl;
        std::cout << "LCM of 4 and 5: " << MyMath::lcm(4, 5) << std::endl;
        std::cout << "Prime factors of 28: ";
        auto factors = MyMath::prime_factors(28);
        for (int factor : factors)
        {
            std::cout << factor << " ";
        }
        std::cout << std::endl;
        std::cout << "Estimated Pi: " << MyMath::calculate_pi(100000) << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}