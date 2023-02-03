#include "source.h"

//  1) Read data from image file (every image is read to the array, that will be translated to input vector)
//  2) Read label - the correct interpretation of image
//  3) Make learn step "train_image_amount" times
void nw::Source::NeuralNetworkLearn(std::string filename_img, std::string filename_lbl, std::function<double(double)> activate_fun_der, double step, double alfa) {
    std::ifstream in_img;
    std::ifstream  in_lbl;
    in_img.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try {
        in_img.open(filename_img);
        in_lbl.open(filename_lbl);
        for(int p = 0; p < train_img_amount; ++p) {
            in_lbl >> true_value_lbl;
            for(int i = 0; i < size_of_input_vector; ++i) {
                in_img >> input_vector[i];
            }
            net_work->LearnStep(input_vector, true_value_lbl, activate_fun_der, step, alfa);
        }
        in_img.close();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

//  Saving weight matrices data to file  (usually use it after learn)
void nw::Source::WeightMatricesAfterLearn(std::string filename_output) {
    std::ofstream file;
    file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try {
        file.open(filename_output);
        for(int k = 0; k < net_work->amount_of_layers - 1; ++k) {
            for(int i = 0; i < net_work->matrices_of_weights[k].amount_of_rows; ++i) {
                file << std::endl;
                for(int j = 0; j < net_work->matrices_of_weights[k].amount_of_columns; ++j) {
                    file << net_work->matrices_of_weights[k].matrix_of_weights[i][j] << " ";
                }
            }
        }
        file.close();
    }
    catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

//  Initializing matrices of weights by data from file
void nw::Source::WeightMatricesInit(std::string filename_input) {
    std::ifstream file;
    file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try {
        file.open(filename_input);
        for(int k = 0; k < net_work->amount_of_layers - 1; ++k) {
            int c = net_work->matrices_of_weights[k].amount_of_columns * net_work->matrices_of_weights[k].amount_of_rows;
            double* array = new double[c];
            for(int v = 0; v < c; ++v) { file >> array[v]; }
            net_work->matrices_of_weights[k].InitMatrixByArray(array);
            delete[] array;
        }
        file.close();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

//  1) Downloads test images from file to Network
//  2) Looks whether results correspond to correct answers
//  3) Counts amount of correct answers
//  4) Prints percentage of correct answers (correct / total * 100)
void nw::Source::Test(int amount_of_tests, std::string filename_input, std::string filename_lbl) {
    std::ifstream in_img;
    std::ifstream  in_lbl;
    in_img.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    int correct_answers = 0;
    try {
        in_img.open(filename_input);
        in_lbl.open(filename_lbl);
        for(int p = 0; p < amount_of_tests; ++p) {
            in_lbl >> true_value_lbl;
            for(int i = 0; i < size_of_input_vector; ++i) {
                in_img >> input_vector[i];
            }
            net_work->layers_of_neurons[0].InitByValues(input_vector);
            net_work->ForwardPass();
            double max = 0;
            int v = 0;
            for(int m = 0; m < net_work->layers_of_neurons[net_work->amount_of_layers - 1].amount_of_neurons; ++m) {
                double tmp = net_work->layers_of_neurons[net_work->amount_of_layers - 1].vector_of_neurons[m];
                if(tmp > max) {
                    max = tmp;
                    v = m;
                }
            }
            if(v == true_value_lbl) {correct_answers++;}
        }
        std::cout << "Total score: " << double(correct_answers) / amount_of_tests * 100 << "% ";
        in_img.close();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

//  1) Not working procedure
//  2) Idea: to mix data while uploading it to network (to increase efficiency of learning)
void nw::Source::NeuralNetworkLearn_2(std::string filename_img, std::string filename_lbl,
                                      std::function<double(double)> activate_fun_der, double step, double alfa,
                                      int generation) {
    std::ifstream in_img;
    std::ifstream  in_lbl;
    in_img.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try {
        in_img.open(filename_img);
        in_lbl.open(filename_lbl);

        std::string str;
        int buffer;

        for(int circle = 0; circle < generation; circle++) {
            //  putting pointer to the file start
            in_lbl.seekg(0);
            in_img.seekg(0);
            //  making a gap
            for(int mess = 0; mess < 28 * circle; mess++) {
                std::getline(in_img, str);
            }
            for(int mess = 0; mess < circle; ++mess) {
                in_lbl  >> buffer;
            }
            //  main loop
            for(int p = 0; p < train_img_amount / generation; ++p) {
                in_lbl >> true_value_lbl;

                for(int i = 0; i < size_of_input_vector; ++i) {
                    in_img >> input_vector[i];
                }

                for(int mess = 0; mess < 28*(generation - 1); mess++) {
                    std::getline(in_img, str);
                }
                for(int mess = 0; mess < (generation - 1); mess++) {
                    in_lbl >> buffer;
                }
                net_work->LearnStep(input_vector, true_value_lbl, activate_fun_der, step, alfa);
            }
        }

        in_img.close();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}