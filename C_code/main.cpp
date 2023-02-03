#include <iostream>
#include "Network.h"
#include "Source.h"
#include <ctime>

int main() {
    using namespace nw;

    std::string input_img = "C:\\Users\\Le\\Desktop\\NeuralNW\\BackPropagation\\C_code\\img_learn.txt";
    std::string input_lbl = "C:\\Users\\Le\\Desktop\\NeuralNW\\BackPropagation\\C_code\\lab_learn.txt";
    std::string output_mat = "C:\\Users\\Le\\Desktop\\NeuralNW\\BackPropagation\\C_code\\weight_matrices_after_learn.txt";
    std::string input_mat = "C:\\Users\\Le\\Desktop\\NeuralNW\\BackPropagation\\C_code\\weight_matrices_after_learn.txt";

    std::string  input_test_img = "C:\\Users\\Le\\Desktop\\NeuralNW\\BackPropagation\\C_code\\img_test.txt";
    std::string  input_test_lab = "C:\\Users\\Le\\Desktop\\NeuralNW\\BackPropagation\\C_code\\lab_test.txt";

    int Layers[] = {784,20, 10};
    Network network1(3, Layers);
    Source source1(784, 1000, &network1);

    for(int i = 1; i < 6; ++i) {
        double start = clock();
        source1.NeuralNetworkLearn(input_img,input_lbl,sigmoid_der_fun, pow(10, -i + 2), 0.7);
        std::cout << "Generation " << i << " ";
        source1.Test(1000, input_test_img,input_test_lab);
        double end = clock();
        std::cout << "Time: " << (end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

    }
    source1.WeightMatricesAfterLearn(output_mat);

    return 0;
}
