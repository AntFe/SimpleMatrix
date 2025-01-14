#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <vector>
#include <stdexcept>

namespace toolkit
{
    class Matrix
    {
    private:
        std::vector<std::vector<float>> data;
        int rows;
        int cols;

    public:
        
        Matrix(int rows, int cols, float initialValue);

        Matrix(std::vector<std::vector<float>> &initialMtx);

        Matrix(int rows, int cols);

        int getRows() const;

        int getCols() const;

        float &operator()(int row, int col);

        float operator()(int row, int col) const;

        Matrix operator*(float scalar) const;

        Matrix operator+(const Matrix &other) const;

        Matrix operator-(const Matrix &other) const;

        Matrix operator*(const Matrix &other) const;

        toolkit::Matrix transform2dScale(float xAxisScale, float yAxisScale);

        toolkit::Matrix transform2dTranslate(float xAxisCoordinate, float yAxisCoordinate);

        toolkit::Matrix transform2dRotate(float angle);

        // Impressão de matriz
        void showMatrix() const;
        };
}

#endif