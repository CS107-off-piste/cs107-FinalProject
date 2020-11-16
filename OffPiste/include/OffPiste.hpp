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

};

#endif /* OFFPISTE_H */
