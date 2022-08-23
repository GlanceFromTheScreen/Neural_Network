#include "ActivationFunction.h"

double nw::sigmoid_fun(double neuron) { return 1 / (1 + exp(-neuron)); }
double nw::sigmoid_der_fun(double neuron) { return neuron * (1 - neuron);}
double nw::del_256(double neuron) {return neuron/256;}
