#include <iostream>
#include "src/Variable.hpp"
#include "src/Function.hpp"
#include "src/BinaryOperator.hpp"
#include "src/UnaryOperator.hpp"

using namespace OP;

int main() {

    // USE CASE 1
    // A function f with 3 inputs a, b, c and 2 outputs u, v.
    float value1 = 0;
    float value2 = 1;
    float value3 = 2;

    float seed1 = 0;
    float seed2 = 0;
    float seed3 = 1;

    Variable a(value1, seed1);
    Variable b(value2, seed2);
    Variable c(value3, seed3);

    // Each EXPRESSION is a scalar function of vector input
    EXPRESSION u = a + b + 1;
    EXPRESSION v = a + exp(1 + c);

    // Combine input nodes and output nodes together respectively
    INPUTS inputs = {a, b, c};
    OUTPUTS outputs = {u, v};

    // Construct the computational graph called f by inputs and outputs.
    Function f(inputs, outputs);

    // evaluate the computational graph and get forward derivative for free!
    VECTOR vec = f.evaluate();
    std::cout<<"u = "<<u.val<<std::endl;    // get output value by output node
    std::cout<<"v = "<<v.val<<std::endl;    // get output value by output node
    std::cout<<"(u, v) = ("<<vec[0]<<", "<<vec[1]<<")"<<std::endl;      // get output values by vec

    std::cout<<std::endl;
    std::cout<<"du/dseed = "<<u.dval<<std::endl;
    std::cout<<"dv/dseed = "<<v.dval<<std::endl;

    std::cout<<std::endl<<"Jacobian Matrix of (u, v) w.r.t (a, b, c): "<<std::endl;
    MATRIX jacob = f.forward_jacobian();
    for (auto &i : jacob) {
        for (auto &j : i) {
            std::cout<<j<<" ";
        }
        std::cout<<std::endl;
    }


    // USE CASE 2



    return 0;
}
