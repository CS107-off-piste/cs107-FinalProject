/* header files */
#include "OffPiste.hpp"

/* explicitly tell compiler to build these templates */
//template class AutoDiff<int>;
//template class AutoDiff<float>;
//template class AutoDiff<double>;

/* ======================== */
/* AutoDiff Class Operators */
/* ======================== */

template <class T>
const AutoDiff<T> AutoDiff<T>::operator+(const AutoDiff<T> &node) const{
    return AutoDiff<T>(v + node.val(), dv + node.dval());
}

template <class T>
AutoDiff<T>& AutoDiff<T>::operator+=(const AutoDiff<T> &node) {
    v += node.val();
    dv += node.dval();
    return *this;
}

template <class T>
const AutoDiff<T> AutoDiff<T>::operator*(const AutoDiff<T> &node) const{
    return AutoDiff<T>(v*node.val(), v*node.dval() + dv*node.val());
}

template <class T>
AutoDiff<T>& AutoDiff<T>::operator*=(const AutoDiff<T> &node) {
    dv = v*node.dval() + dv*node.val();
    v *=node.val();
    return *this;
}

template <class T>
AutoDiff<T>& AutoDiff<T>::operator^(const float alpha) {
    dv = alpha*std::pow(v, alpha-1) * dv;
    v = std::pow(v, alpha);
    return *this;
}

template <class T>
AutoDiff<T> AutoDiff<T>::sin(const AutoDiff<T> &node) {
    // for the function y = sin(x), we expect that:
    //   -> y_value = sin(x_value)
    //   -> y_derivative = cos(x_value) * x_derivative
    T val = std::sin(node.val());
    T dval = std::cos(node.val()) * node.dval();
    return AutoDiff<T>(val,dval);
}

template <class T>
AutoDiff<T> AutoDiff<T>::cos(const AutoDiff<T> &node) {
    // for the function y = cos(x), we expect that:
    //   -> y_value = cos(x_value)
    //   -> y_derivative = -1 * sin(x_value) * x_derivative
    T val = std::cos(node.val());
    T dval = -std::sin(node.val()) * node.dval();
    return AutoDiff<T>(val,dval);
}

template <class T>
AutoDiff<T> AutoDiff<T>::tan(const AutoDiff<T> &node) {
    // for the function y = tan(x), we expect that:
    //   -> y_value = tan(x_value)
    //   -> y_derivative = (sec(x_value))^2 * x_derivative
    // Since sec(x) = 1 / cos(x), this is:
    // (1 / cos(x_value))^2 * x_derivative
    T val = std::tan(node.val());
    T dval = 1.0 / std::pow(std::cos(node.val()), 2) * node.dval();
    return AutoDiff<T>(val,dval);
}

template <class T>
AutoDiff<T> AutoDiff<T>::exp(const AutoDiff<T> &node) {
    // for the function y = exp(x), we expect that
    //  -> y_value = exp(x_value)
    //  -> y_derivative = exp(x_value) * x_derivative 
    T val = std::exp(node.val());
    T dval = std::exp(node.val()) * node.dval();
    return AutoDiff<T>(val,dval);
}
