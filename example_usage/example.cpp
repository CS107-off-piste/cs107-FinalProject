#include <iostream>
#include "../OffPiste/include/Variable.hpp"
#include "../OffPiste/include/Function.hpp"
#include "../OffPiste/include/BinaryOperator.hpp"
#include "../OffPiste/include/UnaryOperator.hpp"

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

    // Each Expression is a scalar function of vector input
    Expression u = a - b + 1;
    Expression v = a + exp(1 + c);

    // Construct the computational graph called f.
    Function f({a,b,c}, {u, v});

    /** Forward Mode Example **/
    std::cout<<"===Forward Example:==="<<std::endl;

    // evaluate the computational graph and get forward derivative for free!
    Vec vec_f = f.evaluate();
    std::cout<<"u = "<<u.val<<std::endl;    // get output value by output node
    std::cout<<"v = "<<v.val<<std::endl;    // get output value by output node
    std::cout<<"(u, v) = ("<<vec_f[0]<<", "<<vec_f[1]<<")"<<std::endl;      // get output values by vec

    std::cout<<std::endl;
    std::cout<<"du/dseed = "<<u.dval<<std::endl;
    std::cout<<"dv/dseed = "<<v.dval<<std::endl;

    std::cout<<std::endl<<"Jacobian Matrix of (u, v) w.r.t (a, b, c): "<<std::endl;
    Mat jacob_f = f.forward_jacobian();
    for (auto &i : jacob_f) {
        for (auto &j : i) {
            std::cout<<j<<" ";
        }
        std::cout<<std::endl;
    }


    /** Reverse Mode Example **/
    std::cout<<std::endl<<"===Backward Example:==="<<std::endl;

    // Combine input nodes and output nodes together respectively
    Input inputs = {a, b, c};
    Output outputs = {u, v};

    // Construct a computational graph called g with the provided inputs and outputs
    Function g(inputs, outputs);

    Vec seeds = {0,0,1}; 
    g.set_seed(seeds);

    Vec vec_b = g.evaluate();
    std::cout<<"u = "<<u.val<<std::endl;    // get output value by output node
    std::cout<<"v = "<<v.val<<std::endl;    // get output value by output node
    std::cout<<"(u, v) = ("<<vec_b[0]<<", "<<vec_b[1]<<")"<<std::endl;      // get output values by vec

    std::cout<<std::endl<<"Jacobian Matrix of (u, v) w.r.t (a, b, c): "<<std::endl;
    Mat jacob_b = g.backward_jacobian();
    for (auto &i : jacob_b) {
        for (auto &j : i) {
            std::cout<<j<<" ";
        }
        std::cout<<std::endl;
    }


    return 0;
}
