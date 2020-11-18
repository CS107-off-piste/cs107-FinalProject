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
const AutoDiff<T> AutoDiff<T>::operator+(const AutoDiff<T> &other) const{
    return AutoDiff<T>(v + other.val(), dv + other.dval());
}

template <class T>
AutoDiff<T>& AutoDiff<T>::operator+=(const AutoDiff<T> &other) {
    v += other.val();
    dv += other.dval();
    return *this;
}

template <class T>
const AutoDiff<T> AutoDiff<T>::operator*(const AutoDiff<T> &other) const{
    return AutoDiff<T>(v*other.val(), v*other.dval() + dv*other.val());
}

template <class T>
AutoDiff<T>& AutoDiff<T>::operator*=(const AutoDiff<T> &other) {
    dv = v*other.dval() + dv*other.val();
    v *=other.val();
    return *this;
}

template <class T>
AutoDiff<T>& AutoDiff<T>::operator^(const float alpha) {
    dv = alpha*std::pow(v, alpha-1) * dv;
    v = std::pow(v, alpha);
    return *this;
}

template <class T>
AutoDiff<T> AutoDiff<T>::sin(const AutoDiff<T> &other) {
    // for the function y = sin(x), we expect that:
    //   -> y_value = sin(x_value)
    //   -> y_derivative = cos(x_value) * x_derivative
    T val = std::sin(other.val());
    T dval = std::cos(other.val()) * other.dval();
    return AutoDiff<T>(val,dval);
}

template <class T>
AutoDiff<T> AutoDiff<T>::exp(const AutoDiff<T> &other) {
    // for the function y = exp(x), we expect that
    //  -> y_value = exp(x_value)
    //  -> y_derivative = exp(x_value) * x_derivative 
    T val = std::exp(other.val());
    T dval = std::exp(other.val()) * other.dval();
    return AutoDiff<T>(val,dval);
}