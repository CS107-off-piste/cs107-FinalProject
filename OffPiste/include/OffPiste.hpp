#ifndef OFFPISTE_H
#define OFFPISTE_H

/* header files */

/* system header files */
#ifndef DOXYGEN_IGNORE

#  include <stdio.h>
#  include <cmath>

#endif


/* =============== */
/* Data Structures */
/* =============== */
template <class T>
class AutoDiff {
  private:
    T v;    /**< value */
    T dv;   /**< derivative value */

  public:

    /* constructors */
    AutoDiff(){};
    AutoDiff(T val,T dval) : v(val),dv(dval) {};

    /* getters */
    T val() const {return v;};
    T dval() const {return dv;};

    /* setters */
    void setval(T val){v = val;}
    void setdval(T dval){dv = dval;}

    void print_hello() const;

    /* ==================== */
    /* overloaded operators */
    /* ==================== */
    const AutoDiff<T> operator+(const AutoDiff<T> &other) const{
        return AutoDiff<T>(v + other.val(), dv + other.dval());
    }

    AutoDiff<T>& operator+=(const AutoDiff<T> &other){
        v += other.val();
        dv += other.dval();
        return *this;
    }

    const AutoDiff<T> operator*(const AutoDiff<T> &other) const {
        return AutoDiff<T>(v*other.val(), v*other.dval() + dv*other.val());
    }

    AutoDiff<T> &operator*=(const AutoDiff<T> &other) {
        dv = v*other.dval() + dv*other.val();
        v *=other.val();
        return *this;
    }

    AutoDiff<T> &operator^(const float alpha) {
        dv = alpha*std::pow(v, alpha-1) * dv;
        v = std::pow(v, alpha);
        return *this;
    }
    /**
     * Apply the sine function to the provided AutoDiff node
     * @param other The AutoDiff node to apply the sine function to
     * @return An AutoDiff object representing the sin of the current AutoDiff object
     */
    static AutoDiff<T> sin(AutoDiff<T> &other) {
        // for the function y = sin(x), we expect that:
        //   -> y_value = sin(x_value)
        //   -> y_derivative = cos(x_value) * x_derivative
        T val = std::sin(other.val());
        T dval = std::cos(other.val()) * other.dval();
        return AutoDiff<T>(val,dval);
    }
};
#endif /* OFFPISTE_H */
