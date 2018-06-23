#include<iomanip>
#include<iostream>

int main(void ) {
    std::cout << std::hex;
    std::cout << std::setiosflags (std::ios::showbase | std::ios::uppercase);
    // std::cout << std::setiosflags (std::ios::showbase);
    std::cout << 100 << std::endl;
    std::cout <<  std::resetiosflags(std::ios::showbase);
    std::cout << 100 << std::endl;

    std::cout << std::setbase(10);
    std::cout << 100 << std::endl;
    std::cout << std::setbase(16);
    std::cout << 100 << std::endl;

    std::cout << std::setbase(10);
    std::cout << std::setfill ('x') << std::setw (10);
    std::cout << 77 << std::endl;

    double f =3.14159;
    std::cout << std::setprecision(5) << f << '\n';
    std::cout << std::setprecision(9) << f << '\n';
    std::cout << std::fixed;
    std::cout << std::setprecision(5) << f << '\n';
    std::cout << std::setprecision(9) << f << '\n';

    return 0;
}

