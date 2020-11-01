#include <iostream>
#include "src/Variable.hpp"
#include "src/Function.hpp"
#include "src/BinaryOperator.hpp"
#include "src/UnaryOperator.hpp"

using namespace OP;

int main() {

    Variable a, b, c;

    a.value = 1;
    b.value = 2;
    c.value = 0;

    EXPRESSION u = a + b;
    EXPRESSION v = a + exp(c);

    EXPRESSIONS outputs = {u, v};

    Function f(outputs);
    std::cout<<"u = "<<f.evaluate(u)<<std::endl;
    std::cout<<"dv/dc = "<<f.forward_derivative(v, c)<<std::endl;

    return 0;
}
