#ifndef OFFPISTE_H
#define OFFPISTE_H

/* header files */

/* system header files */
#ifndef DOXYGEN_IGNORE

#include <stdio.h>

#include <cmath>

#endif

/**
 * @brief A node in the AutoDiff computation graph.
 *
 * Each instance of AutoDiff represents a node in the AutoDiff computation
 * graph. Complicated functions can be composed by chaining multiple nodes. Each
 * node has a function value -- the value of the function. Each node also has a
 * derivative value -- the derivative of the function at the current value.
 */
class AutoDiff {
 private:
  double v;  /**< value */
  double dv; /**< derivative value */

 public:
  /* constructors */
  AutoDiff(){};
  /**
   * Construct an AutoDiff node with the provided value and derivative.
   * @param val The value for this node.
   * @param dval The seed derivative value for this node. By default this is 1.
   */
  AutoDiff(double val, double dval = 1.0) : v(val), dv(dval){};

  /* getters */

  /**
   * Fetch the computed value of this node.
   * @return The value of this node
   */
  double val() const { return v; };
  /**
   * Fetch the derivative value of this node.
   * @return The derivative of this node
   */
  double dval() const { return dv; };

  /* setters */
  void setval(double val) { v = val; }
  void setdval(double dval) { dv = dval; }

  /* ==================== */
  /* overloaded operators */
  /* ==================== */
  //===========================================ADD=============================================
  /**
   * Add two nodes
   * @return A node representing the sum of the two nodes' values.
   */
  const AutoDiff operator+(const AutoDiff &node) const;

  /**
   * Add a constant value to a node.
   * @param a The constant value to add.
   * @param node The node being added to
   * @return A new node representing the sum of the input node and the constant
   * value
   */
  friend AutoDiff operator+(const double a, const AutoDiff &node) {
    AutoDiff a_node = AutoDiff(a, 0);
    return a_node + node;
  };

  /**
   * @see AutoDiff operator+(const double, const AutoDiff&)
   */
  friend AutoDiff operator+(const AutoDiff &node, const double a) {
    return a + node;
  };

  /**
   * Update a node by adding another node's value
   * @return The updated node.
   */
  AutoDiff &operator+=(const AutoDiff &node);

  /**
   * @see AutoDiff::operator+=()
   */
  friend void operator+=(AutoDiff &node, const double a) {
    node.setval(node.val() + a);
  }

  //===========================================SUBSTRACTION=====================================
  /**
   * Unary negation of the provided node
   * @return A new node representing the result of the operation
   */
  const AutoDiff operator-() const;

  /**
   * Subtract one node's value from another
   * @param Node the node to subtract
   * @return A new node representing the first node minus the second node.
   */
  const AutoDiff operator-(const AutoDiff &node) const;

  /**
   * Subtract a constant value from an AutoDiff node
   * @param node The node to subtract from
   * @param a The constant value to subtract
   * @return A new node representing the first node minus the constant.
   */
  friend AutoDiff operator-(const AutoDiff &node, const double a) {
    AutoDiff a_node = AutoDiff(a, 0);
    return node - a_node;
  };

  /**
   * @see AutoDiff::operator-(const AutoDiff&, const double)
   */
  friend AutoDiff operator-(const double a, const AutoDiff &node) {
    AutoDiff a_node = AutoDiff(a, 0);
    return a_node - node;
  };

  /**
   * @see AutoDiff::operator-=(AutoDiff&, double)
   */
  AutoDiff &operator-=(const AutoDiff &node);
  /**
   * Update a node by subtracting another node's value
   * @return The updated node.
   */
  friend void operator-=(AutoDiff &node, const double a) {
    node.setval(node.val() - a);
  }

  //===========================================MULTIPLICATION================================
  /**
   * Multiply one node by another
   * @param node the node to multiply
   * @return A new node representing the first node multiplied by the second
   * node.
   */
  const AutoDiff operator*(const AutoDiff &node) const;

  /**
   * Multiply a node by a constant value
   * @param a The constant value to multiply
   * @param node The node to multiply
   * @return A new new representing the multiplication of the node and constant
   * value
   */
  friend AutoDiff operator*(const double a, const AutoDiff &node) {
    AutoDiff a_node = AutoDiff(a, 0);
    return a_node * node;
  };

  /**
   * @see AutoDiff::operator*(const double, const AutoDiff&)
   */
  friend AutoDiff operator*(const AutoDiff &node, const double a) {
    return a * node;
  };

  /**
   * @see AutoDiff::operator*=(AutoDiff&, double)
   */
  AutoDiff &operator*=(const AutoDiff &node);

  /**
   * Update a node by multiplying another node's value
   * @return The updated node.
   */
  friend void operator*=(AutoDiff &node, const double a) {
    node.setval(node.val() * a);
    node.setdval(node.dval() * a);
  }

  //===========================================DIVISION=====================================
  /**
   * Divide a node by another node
   * @throw Exception On divide by 0
   * @param node the node to divide by
   * @return The new node representing the result of the division operation
   */
  const AutoDiff operator/(const AutoDiff &node) const;

  /**
   * Update a node by dividing another node's value
   * @throw Exception On divide by 0
   * @param node The node to divide by
   * @return The updated node.
   */
  AutoDiff &operator/=(const AutoDiff &node);

  /**
   * Divide a constant value by an AutoDiff node
   * @throw Exception On divide by 0
   * @param a The constant value that is being divided
   * @param node The node to divide by
   * @return A new node representing the result of the operation.
   */
  friend AutoDiff operator/(const double a, const AutoDiff &node) {
    AutoDiff a_node = AutoDiff(a, 0);
    return a_node / node;
  };

  /**
   * @see AutoDiff::operator/(const double, const AutoDiff&)
   */
  friend AutoDiff operator/(const AutoDiff &node, const double a) {
    AutoDiff a_node = AutoDiff(a, 0);
    return node / a_node;
  };

  /**
   * @see AutoDiff::operator/=(const AutoDiff&)
   */
  friend void operator/=(AutoDiff &node, const double a) {
    AutoDiff result = node / a;
    node.setval(result.val());
    node.setdval(result.dval());
  }

  //===========================================POW=============================================
  /**
   * Apply the power function (i.e. base^alpha) with the provided AutoDiff nodes
   * @param base The AutoDiff node that acts as the base
   * @param alpha The AutoDiff node that acts as the power
   * @return An AutoDiff object representing the power function applied to
   * the base AutoDiff object, with alpha as the power
   */
  static AutoDiff pow(const AutoDiff &base, const AutoDiff &alpha);

  /**
   * Apply the power function (i.e. base^alpha) with the provided values
   * @param base The constant value that acts as the base
   * @param alpha The AutoDiff node that acts as the power
   * @return An AutoDiff object representing the power function applied to
   * the base value, with alpha as the power
   */
  static AutoDiff pow(const double base, const AutoDiff &alpha);

  /**
   * Apply the power function (i.e. base^alpha) with the provided values
   * @param base The AutoDiff node that acts as the base
   * @param alpha The constant value that acts as the power
   * @return An AutoDiff object representing the power function applied to
   * the base AutoDiff object, with alpha as the power
   */
  static AutoDiff pow(const AutoDiff &base, const double alpha);

  /**
   * Apply the power function (i.e. base^alpha) with the provided values
   * @param base The constant value that acts as the base
   * @param alpha The constant value that acts as the power
   * @return An AutoDiff object representing the power function applied to
   * the base value, with alpha as the power
   */
  static AutoDiff pow(const double base, const double alpha);

  //====================== TRIGONOMETRIC FUNCTION =============================
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
