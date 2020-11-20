#include <iostream>
#include "../OffPiste/install/include/OffPiste.hpp"

typedef AutoDiff AD;

int main(int argc, char const *argv[])
{
    // some test values
    double value1 = 1.2; 
    double value2 = 3.4;
    double seed1 = 1.0;
    double seed2 = 1.0;

    // construct an AD object 
    // AD is just a shortcut for AutoDiff<double>
    AD x(value1,seed1);
    AD y(value2,seed2);

    // print initial value and seed
    std::cout << "Initial x, y value: " << x.val() << ", "<< y.val() << "\n"; 
    std::cout << "Initial x, y deriv: " << x.dval() << ", "<< y.dval() << "\n";

    // perform the operation z = e^(sin(x + y))
    AD z = AD::exp(AD::sin(x+y));
    std::cout << "Z value, derivative: " << z.val() << ", "<< z.dval() << "\n"; 

    return 0;
}
