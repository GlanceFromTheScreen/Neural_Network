#include "Network.h"
#include "Vector.h"
#include "Matrix.h"
#include "ActivationFunction.h"

//  Memory distribution for Neural network variables
void nw::Network::InitNetwork(int AmountOfLayers, int* NeuronsInLayer) {
    amount_of_layers = AmountOfLayers;
    true_output = -1;
    layers_of_neurons = new Vector[AmountOfLayers];
    for(int i = 0; i < AmountOfLayers; ++i)
    {
        layers_of_neurons[i].MemoryAlloc(NeuronsInLayer[i]);
    }

    matrices_of_weights = new Matrix[AmountOfLayers - 1];
    matrices_of_shift = new Matrix[AmountOfLayers - 1];
    for(int i = 0; i < AmountOfLayers - 1; ++i)
    {
        matrices_of_weights[i].MemoryAlloc(NeuronsInLayer[i], NeuronsInLayer[i+1]);
        matrices_of_shift[i].MemoryAlloc(NeuronsInLayer[i], NeuronsInLayer[i+1]);
        matrices_of_shift[i].InitMatrixByValue(0);
    }

    vector_of_delta = new Vector[AmountOfLayers];
    for(int i = 1; i < AmountOfLayers; ++i)
    {
        vector_of_delta[i].MemoryAlloc(NeuronsInLayer[i]);
    }
}

//  Multiply transported matrix and a vector => result vector update
void nw::Network::Multiply(Matrix &A, Vector &B, Vector &C) {
    double Sum;
    for(int i = 0; i < C.amount_of_neurons; ++i){
        Sum = 0;
        for(int j = 0; j < A.amount_of_rows; ++j) {
            Sum += A.matrix_of_weights[j][i] * B.vector_of_neurons[j];
        }
        C.vector_of_neurons[i] = Sum;
    }
}

//  Forward pass as a step in Back Propagation method
//  (getting the value of the last vector of neurons elements by influence of the first vector)
void nw::Network::ForwardPass() {
    for(int i = 0; i < amount_of_layers - 1; ++i) {
        Multiply(matrices_of_weights[i], layers_of_neurons[i], layers_of_neurons[i+1]);
        layers_of_neurons[i+1].Activate(sigmoid_fun);
    }
}

//  Counting delta components (see photo 1)
void nw::Network::DeltaInit(std::function<double(double)> activate_fun_der) {
    for(int j = 0; j < vector_of_delta[amount_of_layers - 1].amount_of_neurons; ++j) {
        double neuron = layers_of_neurons[amount_of_layers - 1].vector_of_neurons[j];
        if(true_output == j) {
            vector_of_delta[amount_of_layers - 1].vector_of_neurons[j] =
                    (neuron - 1) * activate_fun_der(neuron);
        } else {
            vector_of_delta[amount_of_layers - 1].vector_of_neurons[j] =
                    neuron * activate_fun_der(neuron);
        }
    }

    for(int k = amount_of_layers - 2; k > 0; --k) {
        for(int j = 0; j < vector_of_delta[k].amount_of_neurons; ++j) {
            double Sum = 0;
            for(int l = 0; l < layers_of_neurons[k+1].amount_of_neurons; ++l) {
                Sum += matrices_of_weights[k].matrix_of_weights[j][l] *
                        vector_of_delta[k+1].vector_of_neurons[l];
            }
            vector_of_delta[k].vector_of_neurons[j] =
                    activate_fun_der(layers_of_neurons[k].vector_of_neurons[j]) * Sum;
        }
    }
}

//  Back Propagation - updating matrices of weights by delta values we got
void nw::Network::BackPropagation(double step, double alfa) {
    for(int k = 0; k < amount_of_layers - 1; ++k) {
        for(int i = 0; i < layers_of_neurons[k].amount_of_neurons; ++i) {
            for(int j = 0; j < layers_of_neurons[k+1].amount_of_neurons; ++j) {
                matrices_of_weights[k].matrix_of_weights[i][j] =
                        matrices_of_weights[k].matrix_of_weights[i][j] -
                            alfa*matrices_of_shift[k].matrix_of_weights[i][j] +
                                (1 - alfa) * step * vector_of_delta[k+1].vector_of_neurons[j] *
                                    layers_of_neurons[k].vector_of_neurons[i];
                matrices_of_shift[k].matrix_of_weights[i][j] =
                        alfa*matrices_of_shift[k].matrix_of_weights[i][j] +
                            (1 - alfa) * step * vector_of_delta[k+1].vector_of_neurons[j] *
                                layers_of_neurons[k].vector_of_neurons[i];
            }
        }
    }
}

//  1) One initialization of the first vector
//  2) One Forward Pass
//  3) One weight matrices update
void nw::Network::LearnStep(const double* input_vector, int true_value, std::function<double(double)> activate_fun_der, double step, double alfa) {
    layers_of_neurons[0].InitByValues(input_vector);
    true_output = true_value;
    ForwardPass();
    DeltaInit(activate_fun_der);
    BackPropagation(step, alfa);
}