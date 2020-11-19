#include <iostream>
#include "OffPiste.hpp"

typedef AutoDiff<double> AD; // shortcut for brevity

int main(int argc, char const *argv[])
{
	double value = 9.8f;
    double seed = 1.0f;
    AD x(value,seed);

    std::cout<< x.val();

	return 0;
}