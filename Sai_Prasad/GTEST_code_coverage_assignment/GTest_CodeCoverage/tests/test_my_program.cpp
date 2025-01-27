#include "my_math.h"
#include <gtest/gtest.h>

TEST(MyMathTest, FactorialTest) {
    EXPECT_EQ(MyMath::factorial(3), 6);   
    EXPECT_EQ(MyMath::factorial(4), 24);  //Initial test
    EXPECT_EQ(MyMath::factorial(7), 5040);

    EXPECT_EQ(MyMath::factorial(0), 1);   
    EXPECT_THROW(MyMath::factorial(-5), std::invalid_argument);   //After improvement (edge cases)
    EXPECT_THROW(MyMath::factorial(-999), std::invalid_argument);
}

TEST(MyMathTest, FibonacciTest) {    
    EXPECT_EQ(MyMath::fibonacci(3), 2);   
    EXPECT_EQ(MyMath::fibonacci(4), 3);   //Initial test
    EXPECT_EQ(MyMath::fibonacci(5), 5);  

    EXPECT_EQ(MyMath::fibonacci(0), 0);  
    EXPECT_EQ(MyMath::fibonacci(1), 1);  //After improvement (edge cases)
    EXPECT_THROW(MyMath::fibonacci(-10), std::invalid_argument);  
}

TEST(MyMathTest, GcdTest) {
    EXPECT_EQ(MyMath::gcd(10, 5), 5);     
    EXPECT_EQ(MyMath::gcd(7, 3), 1);      //Initial test
    EXPECT_EQ(MyMath::gcd(14, 21), 7);    

    EXPECT_EQ(MyMath::gcd(0, 5), 5);  
    EXPECT_EQ(MyMath::gcd(5, 0), 5);   //After improvement (edge cases)
    EXPECT_THROW(MyMath::gcd(-10, 5), std::invalid_argument);  
}

TEST(MyMathTest, LcmTest) {
    EXPECT_EQ(MyMath::lcm(4, 5), 20);     
    EXPECT_EQ(MyMath::lcm(6, 8), 24);     //Initial test
    EXPECT_EQ(MyMath::lcm(10, 15), 30);  

    EXPECT_EQ(MyMath::lcm(0, 5), 0);  
    EXPECT_EQ(MyMath::lcm(5, 0), 0);  //After improvement (edge cases)
    EXPECT_THROW(MyMath::lcm(-6, 8), std::invalid_argument);
}

TEST(MyMathTest, PrimeFactorsTest) {
    std::vector<int> factors1 = {2, 2, 3}; 
    EXPECT_EQ(MyMath::prime_factors(12), factors1);
    
    std::vector<int> factors2 = {5};        
    EXPECT_EQ(MyMath::prime_factors(5), factors2);      //Initial test

    std::vector<int> factors3 = {2, 7};     
    EXPECT_EQ(MyMath::prime_factors(14), factors3);

    EXPECT_THROW(MyMath::prime_factors(-10), std::invalid_argument);
    EXPECT_THROW(MyMath::prime_factors(1), std::invalid_argument);   //After improvement (edge cases)
}

TEST(MyMathTest, PiCalculationTest) {
    EXPECT_NEAR(MyMath::calculate_pi(100), 3.13159, 0.01);  
    EXPECT_NEAR(MyMath::calculate_pi(1000), 3.14059, 0.01); //Initial test

    EXPECT_THROW(MyMath::calculate_pi(0), std::invalid_argument); 
    EXPECT_THROW(MyMath::calculate_pi(-100), std::invalid_argument);    //After improvement (edge cases)
}

TEST(MyMathTest, SigmoidTest) {
    EXPECT_NEAR(MyMath::sigmoid(0), 0.5, 0.01);    
    EXPECT_NEAR(MyMath::sigmoid(1), 0.731, 0.01);  //Initial test
    EXPECT_NEAR(MyMath::sigmoid(-1), 0.269, 0.01); 
}

TEST(MyMathTest, ReluTest) {
    EXPECT_EQ(MyMath::relu(5), 5);      
    EXPECT_EQ(MyMath::relu(-3), 0);     //Initial test
    EXPECT_EQ(MyMath::relu(0), 0);      
}

TEST(MyMathTest, MeanSquaredErrorTest) {
    std::vector<double> y_true = {3.0, 4.0, 5.0};
    std::vector<double> y_pred = {3.0, 4.1, 4.9};
    EXPECT_NEAR(MyMath::mean_squared_error(y_true, y_pred), 0.00667, 0.00001);

    y_true = {1.0, 2.0, 3.0, 4.0};
    y_pred = {1.1, 1.9, 3.1, 3.9};
    EXPECT_NEAR(MyMath::mean_squared_error(y_true, y_pred), 0.01000, 0.00001); //Initial test

    y_true = {1.0};
    y_pred = {2.0, 3.0};
    EXPECT_THROW(MyMath::mean_squared_error(y_true, y_pred), std::invalid_argument); //After improvement (edge cases)

}

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }