#include <iostream>
#include "../OffPiste/install/include/OffPiste.hpp"

typedef AutoDiff AD;

int main(int argc, char const *argv[])
{
    double value = 2.0;
    double seed = 1.0;

    // construct an AD object 
    // AD is just a shortcut for AutoDiff<double>
    AD x(value, seed);

    AD v = AD::exp(AD::sin(x)) - AD::cos(x^0.5);
    std::cout << "V value, derivative: " << v.val() << ", "<< v.dval() << "\n";

    AD w = AD::exp(AD::sin(x)) - AD::cos(x^0.5) * AD::sin(((AD::cos(x)^2) + (x^2))^0.5);
    std::cout << "W value, derivative: " << w.val() << ", "<< w.dval() << "\n";

    return 0;
}
