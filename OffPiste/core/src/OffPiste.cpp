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
void AutoDiff<T>::print_hello() const {
    printf("Hello\n");
}
