//1.4 Инвертируйте значение бита в числе N по его номеру K.

#include <iostream>

int main() {
    unsigned num, i;
    std::cin >> num >> i;
    
    std::cout << (num ^ (1 << i)) << '\n';

    return 0;
}