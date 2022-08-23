#ifndef C_CODE_VECTOR_H
#define C_CODE_VECTOR_H
#include <iostream>
#include <functional>

namespace nw {
    class Vector {
    public:
        double *vector_of_neurons;
        int amount_of_neurons;
    public:
        Vector() : vector_of_neurons(nullptr), amount_of_neurons(0) {}
        Vector(int AmountOfNeurons) { this->MemoryAlloc(AmountOfNeurons); }
        ~Vector() { delete[] this->vector_of_neurons; }

        void MemoryAlloc(int AmountOfNeurons);
        void InitByValues(const double *values);
        void Print();
        void Activate(std::function<double(double)> f);
    };
}

#endif
