#ifndef C_CODE_MATRIX_H
#define C_CODE_MATRIX_H
#include <random>

namespace nw {
    class Matrix {
    public:
        double** matrix_of_weights;
        int amount_of_rows;
        int amount_of_columns;
    public:
        Matrix() : matrix_of_weights(nullptr), amount_of_rows(0), amount_of_columns(0) {}
        Matrix(int Rows, int Columns) { this->MemoryAlloc(Rows, Columns); }
        ~Matrix() {
            for(int i = 0; i < this->amount_of_rows; ++i) {delete[] this->matrix_of_weights[i];}
            delete[] this->matrix_of_weights;
        }

        void MemoryAlloc(int Rows, int Columns);
        void PrintMatrix();
        void InitMatrixByValue(double value);
        void InitMatrixByArray(double* array);
    };
}

#endif
