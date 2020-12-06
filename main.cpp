#include <iostream>
#include "src/Variable.hpp"
#include "src/Function.hpp"
#include "src/BinaryOperator.hpp"
#include "src/UnaryOperator.hpp"

using namespace OP;

int main() {

    // A function f with 3 inputs a, b, c and 2 outputs u, v.
    float value1 = 1;
    float value2 = 2;
    float value3 = 3;

    float seed1 = 0;
    float seed2 = 0;
    float seed3 = 1;

    Variable a(value1, seed1);
    Variable b(value2, seed2);
    Variable c(value3, seed3);

    // Each EXPRESSION is a scalar function of vector input
    EXPRESSION u = a - b + 1;
    EXPRESSION v = a + exp(1 + c);

    // Combine input nodes and output nodes together respectively
    INPUTS inputs = {a, b, c};
    OUTPUTS outputs = {u, v};

    // Construct the computational graph called f by inputs and outputs.
    Function f(inputs, outputs);


    /** Forward Mode Example**/
    std::cout<<"Forward Example:"<<std::endl;

    // evaluate the computational graph and get forward derivative for free!
    VECTOR vec_f = f.evaluate();
    std::cout<<"u = "<<u.val<<std::endl;    // get output value by output node
    std::cout<<"v = "<<v.val<<std::endl;    // get output value by output node
    std::cout<<"(u, v) = ("<<vec_f[0]<<", "<<vec_f[1]<<")"<<std::endl;      // get output values by vec

    std::cout<<std::endl;
    std::cout<<"du/dseed = "<<u.dval<<std::endl;
    std::cout<<"dv/dseed = "<<v.dval<<std::endl;

    std::cout<<std::endl<<"Jacobian Matrix of (u, v) w.r.t (a, b, c): "<<std::endl;
    MATRIX jacob_f = f.forward_jacobian();
    for (auto &i : jacob_f) {
        for (auto &j : i) {
            std::cout<<j<<" ";
        }
        std::cout<<std::endl;
    }


    /** Reverse Mode Example**/
    std::cout<<std::endl<<"Backward Example:"<<std::endl;

    VECTOR vec_b = f.evaluate();
    std::cout<<"u = "<<u.val<<std::endl;    // get output value by output node
    std::cout<<"v = "<<v.val<<std::endl;    // get output value by output node
    std::cout<<"(u, v) = ("<<vec_b[0]<<", "<<vec_b[1]<<")"<<std::endl;      // get output values by vec

    std::cout<<std::endl;

    f.zero_grad();      // call f.zero_grad() to set grads of all nodes in the graph f to zero
    u.backward();
    std::cout<<"(du/da, du/db, du/dc) = ("<<a.grad<<", "<<b.grad<<", "<<c.grad<<")"<<std::endl;


    f.zero_grad();      // call f.zero_grad() to set grads of all nodes in the graph f to zero
    v.backward();
    std::cout<<"(dv/da, dv/db, dv/dc) = ("<<a.grad<<", "<<b.grad<<", "<<c.grad<<")"<<std::endl;

    std::cout<<std::endl<<"Jacobian Matrix of (u, v) w.r.t (a, b, c): "<<std::endl;
    MATRIX jacob_b = f.backward_jacobian();
    for (auto &i : jacob_b) {
        for (auto &j : i) {
            std::cout<<j<<" ";
        }
        std::cout<<std::endl;
    }


    return 0;
}
