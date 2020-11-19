#ifndef OFFPISTE_H
#define OFFPISTE_H

/* header files */

/* system header files */
#ifndef DOXYGEN_IGNORE

#include <stdio.h>

#include <cmath>

#endif

/* =============== */
/* Data Structures */
/* =============== */

class AutoDiff {
 private:
  double v;  /**< value */
  double dv; /**< derivative value */

 public:
  /* constructors */
  AutoDiff(){};
  AutoDiff(double val, double dval = 1.0) : v(val), dv(dval){};

  /* getters */
  double val() const { return v; };
  double dval() const { return dv; };

  /* setters */
  void setval(double val) { v = val; }
  void setdval(double dval) { dv = dval; }

  /* ==================== */
  /* overloaded operators */
  /* ==================== */
  //===========================================ADD=============================================
  const AutoDiff operator+(const AutoDiff &node) const;

  friend AutoDiff operator+(const double a, const AutoDiff &node) {
    AutoDiff a_node = AutoDiff(a, 0);
    return a_node + node;
  };

  friend AutoDiff operator+(const AutoDiff &node, const double a) {
    return a + node;
  };

  AutoDiff &operator+=(const AutoDiff &node);

  friend void operator+=(AutoDiff &node, const double a) {
    node.setval(node.val() + a);
  }

  //===========================================SUBSTRACTION=====================================
  const AutoDiff operator-(const AutoDiff &node) const;

  // handle, e.g. AutoDiff<double> - 5.0
  friend AutoDiff operator-(const AutoDiff &node, const double a) {
    AutoDiff a_node = AutoDiff(a, 0);
    return node - a_node;
  };

  // handle, e.g. 5.0 - AutoDiff<double>
  friend AutoDiff operator-(const double a, const AutoDiff &node) {
    AutoDiff a_node = AutoDiff(a, 0);
    return a_node - node;
  };

  AutoDiff &operator-=(const AutoDiff &node);

  friend void operator-=(AutoDiff &node, const double a) {
    node.setval(node.val() - a);
  }

  //===========================================MULTIPLICATION================================
  const AutoDiff operator*(const AutoDiff &node) const;

  friend AutoDiff operator*(const double a, const AutoDiff &node) {
    AutoDiff a_node = AutoDiff(a, 0);
    return a_node * node;
  };

  friend AutoDiff operator*(const AutoDiff &node, const double a) {
    return a * node;
  };

  AutoDiff &operator*=(const AutoDiff &node);

  friend void operator*=(AutoDiff &node, const double a) {
    node.setval(node.val() * a);
    node.setdval(node.dval() * a);
  }

  //===========================================DIVISION=====================================
  const AutoDiff operator/(const AutoDiff &node) const;

  AutoDiff &operator/=(const AutoDiff &node);

  // handle, e.g. 5.0 / Autodiff<double>
  friend AutoDiff operator/(const double a, const AutoDiff &node) {
    AutoDiff a_node = AutoDiff(a, 0);
    return a_node / node;
  };

  // handle, e.g. Autodiff<double> / 5.0
  friend AutoDiff operator/(const AutoDiff &node, const double a) {
    AutoDiff a_node = AutoDiff(a, 0);
    return node / a_node;
  };

  friend void operator/=(AutoDiff &node, const double a) {
    AutoDiff result = node / a;
    node.setval(result.val());
    node.setdval(result.dval());
  }

  //===========================================POW=============================================
  AutoDiff &operator^(const float alpha);

  AutoDiff &operator^(const AutoDiff &node);

  friend AutoDiff operator^(const double a, const AutoDiff &node) {
    AutoDiff a_node = AutoDiff(a, 0);
    return a_node ^ node;
  }

  /**
   * Apply the sine function to the provided AutoDiff node
   * @param node The AutoDiff node to apply the sine function to
   * @return An AutoDiff object representing the sin of the current AutoDiff
   * object
   */
  static AutoDiff sin(const AutoDiff &node);

  /**
   * Apply the cosine function to the provided AutoDiff node
   * @param node The AutoDiff node to apply the cosine function to
   * @return An AutoDiff object representing the cosine of the current AutoDiff
   * object
   */
  static AutoDiff cos(const AutoDiff &node);

  /**
   * Apply the tangent function to the provided AutoDiff node
   * @param node The AutoDiff node to apply the tangent function to
   * @return An AutoDiff object representing the tangent of the current AutoDiff
   * object
   */
  static AutoDiff tan(const AutoDiff &node);

  /**
   * Apply the exponential function (i.e. e^x) to the provided AutoDiff node
   * @param node The AutoDiff node to apply the exponential function to
   * @return An AutoDiff object representing the exponential function applied to
   * the current AutoDiff object
   */
  static AutoDiff exp(const AutoDiff &node);
};
#endif /* OFFPISTE_H */
