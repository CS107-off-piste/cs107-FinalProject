/* header files */
#include "OffPiste.hpp"

#include <cmath>
#include <iostream>

/* ======================== */
/* AutoDiff Class Operators */
/* ======================== */
bool equal(double a, double b) {
  if (std::abs(a - b) < 1e-15) return true;
  return false;
}

const AutoDiff AutoDiff::operator+(const AutoDiff &node) const {
  return AutoDiff(v + node.val(), dv + node.dval());
}

AutoDiff &AutoDiff::operator+=(const AutoDiff &node) {
  v += node.val();
  dv += node.dval();
  return *this;
}

const AutoDiff AutoDiff::operator-() const {
  // unary negation -> invert value and derivative
  return AutoDiff(-this->val(), -this->dval());  
}

const AutoDiff AutoDiff::operator-(const AutoDiff &node) const {
  return AutoDiff(v - node.val(), dv - node.dval());
}

AutoDiff &AutoDiff::operator-=(const AutoDiff &node) {
  v -= node.val();
  dv -= node.dval();
  return *this;
}

const AutoDiff AutoDiff::operator*(const AutoDiff &node) const {
  return AutoDiff(v * node.val(), v * node.dval() + dv * node.val());
}

AutoDiff &AutoDiff::operator*=(const AutoDiff &node) {
  dv = v * node.dval() + dv * node.val();
  v *= node.val();
  return *this;
}

const AutoDiff AutoDiff::operator/(const AutoDiff &node) const {
  if (equal(node.val(), 0.0)) {
    throw "Divide by zero";
  }

  return AutoDiff(v / node.val(),
                  // quotient rule for differentiation
                  (dv * node.val() - node.dval() * v) / pow(node.val(), 2));
}

AutoDiff &AutoDiff::operator/=(const AutoDiff &node) {
  if (equal(node.val(), 0.0)) {
    throw "Divide by zero";
  }
  dv = (dv * node.val() - node.dval() * v) /
       pow(node.val(), 2);  // quotient rule for differentiation
  v = v / node.val();
  return *this;
}

AutoDiff &AutoDiff::operator^(const float alpha) {
  dv = alpha * std::pow(v, alpha - 1) * dv;  // power rule for differentiation
  v = std::pow(v, alpha);
  return *this;
}

AutoDiff &AutoDiff::operator^(const AutoDiff &node) {
  dv = node.val() * std::pow(v, node.val() - 1) * dv +
       std::pow(v, node.val()) * std::log(v) * node.dval();
  v = std::pow(v, node.val());
  return *this;
}

AutoDiff AutoDiff::sin(const AutoDiff &node) {
  // for the function y = sin(x), we expect that:
  //   -> y_value = sin(x_value)
  //   -> y_derivative = cos(x_value) * x_derivative
  double val = std::sin(node.val());
  double dval = std::cos(node.val()) * node.dval();
  return AutoDiff(val, dval);
}

AutoDiff AutoDiff::cos(const AutoDiff &node) {
  // for the function y = cos(x), we expect that:
  //   -> y_value = cos(x_value)
  //   -> y_derivative = -1 * sin(x_value) * x_derivative
  double val = std::cos(node.val());
  double dval = -std::sin(node.val()) * node.dval();
  return AutoDiff(val, dval);
}

AutoDiff AutoDiff::tan(const AutoDiff &node) {
  // for the function y = tan(x), we expect that:
  //   -> y_value = tan(x_value)
  //   -> y_derivative = (sec(x_value))^2 * x_derivative
  // Since sec(x) = 1 / cos(x), this is:
  // (1 / cos(x_value))^2 * x_derivative
  double val = std::tan(node.val());
  double dval = 1.0 / std::pow(std::cos(node.val()), 2) * node.dval();
  return AutoDiff(val, dval);
}

AutoDiff AutoDiff::exp(const AutoDiff &node) {
  // for the function y = exp(x), we expect that
  //  -> y_value = exp(x_value)
  //  -> y_derivative = exp(x_value) * x_derivative
  double val = std::exp(node.val());
  double dval = std::exp(node.val()) * node.dval();
  return AutoDiff(val, dval);
}
