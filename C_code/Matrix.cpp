#include "Matrix.h"
#include <iostream>

//  1) Memory allocation
//  2) Initialization matrix elements by random number (from 0 to 1)
void nw::Matrix::MemoryAlloc(int Rows, int Columns) {
    matrix_of_weights = new double*[Rows];
    amount_of_rows = Rows;
    amount_of_columns = Columns;
    int v = 1;
    for(int i = 0; i < Rows; ++i) {
        matrix_of_weights[i] = new double[Columns];
        for(int j = 0; j < Columns; ++j) {
            srand(v);
            double r = ((double)(rand() % 10))/10;
            matrix_of_weights[i][j] = r;
            v++;
        }
    }
}

//  Matrix print
void nw::Matrix::PrintMatrix() {
        for(int i = 0; i < amount_of_rows; ++i) {
            std::cout << std::endl;
            for(int j = 0; j < amount_of_columns; ++j) {
                std::cout << matrix_of_weights[i][j] << " ";
            }
        }
}

//  Matrix init by integer input value
void nw::Matrix::InitMatrixByValue(double value) {
    for(int i = 0; i < amount_of_rows; ++i) {
        for(int j = 0; j < amount_of_columns; ++j) {
            matrix_of_weights[i][j] = value;
        }
    }
}

//  Matrix init by array (filling row by row)
void nw::Matrix::InitMatrixByArray(double* array) {
    int v = 0;
    for(int i = 0; i < amount_of_rows; ++i) {
        for(int j = 0; j < amount_of_columns; ++j) {
            matrix_of_weights[i][j] = array[v];
            v++;
        }
    }
}

