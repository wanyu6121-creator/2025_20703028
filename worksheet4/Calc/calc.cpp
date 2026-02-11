#include <iostream>
#include <sstream>
#include <string>
#include "adder.h"

int main(int argc, char *argv[]) {
    int a, b, c;
    if (argc != 3) return 1;

    std::stringstream ssa(argv[1]);
    std::stringstream ssb(argv[2]);

    ssa >> a;
    ssb >> b;

    c = add(a, b);

    std::cout << c << std::endl;

    return 0;
}