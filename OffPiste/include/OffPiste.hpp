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
    AutoDiff(T val,T dval=1.0) : v(val),dv(dval) {};

    /* getters */
    T val() const {return v;};
    T dval() const {return dv;};

    /* setters */
    void setval(T val){v = val;}
    void setdval(T dval){dv = dval;}

    /* ==================== */
    /* overloaded operators */
    /* ==================== */
    const AutoDiff<T> operator+(const AutoDiff<T> &node) const;
	
	friend AutoDiff<T> operator+(const T a, const AutoDiff<T> &node) {
		AutoDiff<T> a_node = AutoDiff<T>(a, 0);
		return a_node + node;
	};

	friend AutoDiff<T> operator+(const AutoDiff<T> &node, const T a) {return a + node;};

    AutoDiff<T> &operator+=(const AutoDiff<T> &node);

	const AutoDiff<T> operator-(const AutoDiff<T> &node) const;

    // handle, e.g. AutoDiff<double> - 5.0 
    friend AutoDiff<T> operator-(const AutoDiff<T> &node, const T a) {
        AutoDiff<T> a_node = AutoDiff<T>(a, 0);
        return node - a_node;
    };

	AutoDiff<T> &operator-=(const AutoDiff<T> &node);

    const AutoDiff<T> operator*(const AutoDiff<T> &node) const;

    AutoDiff<T> &operator*=(const AutoDiff<T> &node);

	const AutoDiff<T> operator/(const AutoDiff<T> &node) const;

	AutoDiff<T> &operator/=(const AutoDiff<T> &node) ;

    AutoDiff<T> &operator^(const float alpha);

    /**
     * Apply the sine function to the provided AutoDiff node
     * @param node The AutoDiff node to apply the sine function to
     * @return An AutoDiff object representing the sin of the current AutoDiff object
     */
    static AutoDiff<T> sin(const AutoDiff<T> &node);

    /**
     * Apply the exponential function (i.e. e^x) to the provided AutoDiff node
     * @param node The AutoDiff node to apply the exponential function to
     * @return An AutoDiff object representing the exponential function applied to the current AutoDiff object
     */
    static AutoDiff<T> exp(const AutoDiff<T> &node);
};
#endif /* OFFPISTE_H */
