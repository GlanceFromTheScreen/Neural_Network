#ifndef C_CODE_ACTIVATIONFUNCTION_H
#define C_CODE_ACTIVATIONFUNCTION_H
#include <functional>
#include <cmath>

namespace nw {
    double sigmoid_fun(double neuron);
    double sigmoid_der_fun(double neuron);
    double reLU_fun(double neuron);
    double thx_fun(double neuron);
    double del_256(double neuron);
}

#endif
