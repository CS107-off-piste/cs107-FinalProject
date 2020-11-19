/* header files */
#include "OffPiste.hpp"
#include<iostream>
/* explicitly tell compiler to build these templates */
//template class AutoDiff<int>;
//template class AutoDiff<float>;
//template class AutoDiff<double>;

/* ======================== */
/* AutoDiff Class Operators */
/* ======================== */
bool equal(double a, double b) {
	if (abs(a - b) < 1e-15)
		return true;
	return false;
}
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
const AutoDiff<T> AutoDiff<T>::operator-(const AutoDiff<T> &node) const {
	return AutoDiff<T>(v - node.val(), dv - node.dval());
}

template <class T>
AutoDiff<T>& AutoDiff<T>::operator-=(const AutoDiff<T> &node) {
	v -= node.val();
	dv -= node.dval();
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
const AutoDiff<T> AutoDiff<T>::operator/(const AutoDiff<T> &node) const {
	if (equal(node.val(), 0.0))
		throw "Divide by zero";
	//if (sizeof(node.val()) == 4)
		//return AutoDiff<float>(v / (float)node.val(), (dv*node.val() - node.dval()*v) / (float)pow(node.val(), 2));
	return AutoDiff<T>(v / node.val(), (dv*node.val() - node.dval()*v) / pow(node.val(), 2));
}

template <class T>
AutoDiff<T>& AutoDiff<T>::operator/=(const AutoDiff<T> &node) {
	if (equal(node.val(), 0.0))
		throw "Divide by zero";
	/*if (sizeof(node.val()) == 4) {
		v = v / (float)node.val();
		dv = (dv*node.val() - node.dval()*v) / (float)pow(node.val(), 2);
		return *this;
	}*/
	dv = (dv*node.val() - node.dval()*v) / pow(node.val(), 2);
	v = v / node.val();
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
AutoDiff<T> AutoDiff<T>::exp(const AutoDiff<T> &node) {
    // for the function y = exp(x), we expect that
    //  -> y_value = exp(x_value)
    //  -> y_derivative = exp(x_value) * x_derivative 
    T val = std::exp(node.val());
    T dval = std::exp(node.val()) * node.dval();
    return AutoDiff<T>(val,dval);
}
