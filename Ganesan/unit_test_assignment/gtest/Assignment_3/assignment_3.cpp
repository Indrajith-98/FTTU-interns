#include <iostream>
#include "fibonacci.h"
using namespace std;


int main() {
    int n;
    cout << "Enter the number of terms: ";
    cin >> n;
    fibonacci(n);
    return 0;
}
