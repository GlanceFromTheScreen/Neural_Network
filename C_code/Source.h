#ifndef C_CODE_SOURCE_H
#define C_CODE_SOURCE_H
#include <fstream>
#include <string>
#include "Network.h"
#include "ActivationFunction.h"

namespace nw {
    class Source {
    public:
        Network* net_work;
        double* input_vector;
        int size_of_input_vector;
        int train_img_amount;
        int true_value_lbl;
    public:
        Source(int size_of_input_vector_, int train_img_amount_, Network* network_) {
            train_img_amount = train_img_amount_;
            size_of_input_vector = size_of_input_vector_;
            input_vector = new double [size_of_input_vector_];
            net_work = network_;
        }
        ~Source() {delete[] input_vector;}

        void NeuralNetworkLearn(std::string filename_img, std::string filename_lbl, std::function<double(double)> activate_fun_der, double step, double alfa);
        void WeightMatricesAfterLearn(std::string filename_output);
        void WeightMatricesInit(std::string filename_input);
        void Test(int amount_of_tests, std::string filename_input, std::string filename_lbl);
        void NeuralNetworkLearn_2(std::string filename_img, std::string filename_lbl, std::function<double(double)> activate_fun_der, double step, double alfa, int generation);

    };
}

#endif