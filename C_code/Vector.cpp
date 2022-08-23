#include "Vector.h"
#include <iostream>

//  1) Memory allocation
//  2) Initialization vector components by 82 (random number)
void nw::Vector::MemoryAlloc(int AmountOfNeurons) {
    this->vector_of_neurons = new double[AmountOfNeurons];
    this->amount_of_neurons = AmountOfNeurons;
    for(int i = 0; i < AmountOfNeurons; ++i) {
        this->vector_of_neurons[i] = 82;
    }
}

//  Initialization by input value
void nw::Vector::InitByValues(const double* values) {
    for(int i = 0; i < this->amount_of_neurons; ++i) {
        this->vector_of_neurons[i] = values[i];
    }
}

//  Vector print
void nw::Vector::Print() {
    for(int i = 0; i < this->amount_of_neurons; ++i) {
        std::cout << this->vector_of_neurons[i] << " ";
    }
    std::cout << std::endl;
}

//  1) Dividing vector component into 10
//  (otherwise vector components as a big numbers will be the same after activation - property of act. functions)
//  2) Activate function applying to vector components
void nw::Vector::Activate(std::function<double(double)> activate_function) {
    for(int i = 0; i < this->amount_of_neurons; ++i) {
        this->vector_of_neurons[i] = activate_function(this->vector_of_neurons[i] / 10);
    }
}