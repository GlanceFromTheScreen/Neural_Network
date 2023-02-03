#ifndef C_CODE_NETWORK_H
#define C_CODE_NETWORK_H
#include "Vector.h"
#include "Matrix.h"
#include "ActivationFunction.h"

namespace nw {

    class Network {
    public:
        Vector* layers_of_neurons;
        Matrix* matrices_of_weights;
        Matrix* matrices_of_shift;
        Vector* vector_of_delta;
        int true_output;
        int amount_of_layers;
        friend Vector;

    public:
        Network() {
            layers_of_neurons = nullptr;
            matrices_of_weights = nullptr;
            matrices_of_shift = nullptr;
            vector_of_delta = nullptr;
            true_output = -1;
            amount_of_layers = 0;
        }

        Network(int AmountOfLayers, int* NeuronsInLayer) {
            InitNetwork(AmountOfLayers, NeuronsInLayer);
        }

        ~Network() {
            delete[] layers_of_neurons;
            delete[]  matrices_of_weights;
            delete[] matrices_of_shift;
            delete[] vector_of_delta;
        }

        void InitNetwork(int AmountOfLayers, int* NeuronsInLayer);
        void Multiply(Matrix& A, Vector& B, Vector& C);
        void ForwardPass();
        void DeltaInit(std::function<double(double)> activate_fun_der);
        void BackPropagation(double step, double alfa);
        void LearnStep(const double* input_vector, int true_value, std::function<double(double)> activate_fun_der, double step, double alfa);
    };

}



#endif
