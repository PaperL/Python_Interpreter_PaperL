#include <iostream>

#include "HighPrecision.h"

int main() {
    HighPrecision a, b, c;
    while (1) {
        std::cin >> a >> b;
        std::cout << "+: " << a + b << std::endl;
        std::cout << "-: " << a - b << std::endl;
        std::cout << "*: " << a * b << std::endl;
        std::cout << "/: " << a / b << std::endl;
        std::cout << "%: " << a % b << std::endl;
    }
    return 0;
}