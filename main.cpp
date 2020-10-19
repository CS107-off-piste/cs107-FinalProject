#include <iostream>
#include "src/Variable.hpp"
#include "src/Graph.hpp"
#include "src/BinaryOperator.hpp"
#include "src/UnaryOperator.hpp"

using namespace OP;

int main() {

    Variable a, b, c;

    a.value = 1;
    b.value = 2;
    c.value = 3;

    EXPRESSION f = a + c;
    EXPRESSION g = a + exp(b);

    EXPRESSIONS outputs = {f, g};

    Graph graph(outputs);
    std::cout<<"f = "<<graph.evaluate(f)<<std::endl;
    std::cout<<"dg/db = "<<graph.forward_derivative(g, b)<<std::endl;

    return 0;
}
