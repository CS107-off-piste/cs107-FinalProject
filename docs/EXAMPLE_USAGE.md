## How to use *AutoD*

### **How do you envision that a user will interact with your package?**  
*AutoD* will be used as an API.   

### **What should they import?**  
They should download *AutoD.lib* , set the search directory and include the header file `#include<AutoD.h>`.  

### **How can they instantiate AD objects?**  
#### For single-variable function
```
#include<iostream>
#include<AutoD.h>
using namespace AutoD;

int main(){
    
    Variable x = 2.0;
    Function f = func(exp(cos(x + 3) + pow(x, 4)) + 1);
    std::cout<<"f = "<<f.evaluate()<<std::endl;
    std::cout<<"df/dx = "<<f.forward_derivative(x)<<std::endl;
    
}
```
#### For Multi-variable function
```
#include<iostream>
#include<AutoD.h>
using namespace AutoD;

int main(){
    
    Variable x = 2.0, y = 3.0, z = 4.0;
    Function u = func(exp(cos(x + 3) + pow(y, 4)) + z);
    std::cout<<"f = "<<f.evaluate()<<std::endl;
    std::cout<<"df/dx = "<<f.forward_derivative(x)<<std::endl;
    std::cout<<"df/dy = "<<f.forward_derivative(y)<<std::endl;
    std::cout<<"df/dz = "<<f.forward_derivative(z)<<std::endl;
    std::cout<<"Gradient of f"<<f.forward_gradient()<<std::endl;  //gradient of f: (dfdx, dfdy, dfdz)
    
}
```
#### For Vector function
```
#include<iostream>
#include<AutoD.h>
using namespace AutoD;

int main(){
    
    Variable x = 2.0, y = 3.0, z = 4.0;
    Expression u = exp(cos(x + 3) + pow(y, 4)) + z;
    Expression v = x + y;
    
    Function F = func(u,v) //F is the vector function.
    
    std::cout<<"F = "<<F.evaluate()<<std::endl;
    std::cout<<"dF/dx = "<<F.forward_derivative(x)<<std::endl;
    std::cout<<"dF/dy = "<<F.forward_derivative(y)<<std::endl;
    std::cout<<"dF/dz = "<<F.forward_derivative(z)<<std::endl;
    std::cout<<"Jacobian of F"<<F.Jacobian(x,y,z)<<std::endl;
}   
```
