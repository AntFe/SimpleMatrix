#include "matrix.h"
#include <math.h>

using namespace toolkit;
using namespace std;

// construtor não recomendado
toolkit::Matrix::Matrix(int rows, int cols, float initialValue) : rows(rows), cols(cols), data(rows, std::vector<float>(cols, initialValue))
{

}

toolkit::Matrix::Matrix(std::vector<std::vector<float>>& initialMtx) : data(initialMtx)
{
    this->rows = initialMtx.size();
    this->cols = (initialMtx.empty()) ? 0 : initialMtx[0].size();
    for (const auto &row : initialMtx)
    {
        if (row.size() != cols)
            throw std::invalid_argument("Todas as linhas devem ter o mesmo número de colunas.");
    }
}

toolkit::Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols)
{
    /// cria uma matriz identidade

    // inicializar os vetores é importante
    try{
    this->data = std::vector<std::vector<float>>(rows, std::vector<float>(cols));
    }
    catch(const std::bad_alloc& vctException){
        throw std::runtime_error("Falha ao alocar o vetor ao construir a matriz");
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int k = 0; k < cols; ++k)
        {
            this->data[i][k] = (i == k) ? 1.0 : 0.0;
        }
    }
}

int toolkit::Matrix::getRows() const
{
    return this->rows;
}

int toolkit::Matrix::getCols() const
{
    return this->cols;
}

/// rever esse erro
//operador com problema
float &toolkit::Matrix::operator()(int row, int col)
{
    if (row < 0 || row >= this->rows || col < 0 || col >= this->cols)
    {
        throw std::out_of_range("Índice fora do intervalo.");
    }
    return this->data[row][col];
}


float toolkit::Matrix::operator()(int row, int col) const
{
    if (row >= rows || col >= cols)
    {
        throw std::out_of_range("Índice fora do intervalo.");
    }
    return data[row][col];
}

toolkit::Matrix toolkit::Matrix::operator*(float scalar) const
{
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i)
    {
        for (int k = 0; k < cols; ++k)
        {
            result(i, k) = data[i][k] * scalar;
        }
    }
    return result;
}

toolkit::Matrix toolkit::Matrix::operator+(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
    {
        throw std::invalid_argument("Dimensões das matrizes incompatíveis para soma.");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i)
    {
        for (int k = 0; k < cols; ++k)
        {
            result(i, k) = data[i][k] + other(i, k);
        }
    }
    return result;
}

toolkit::Matrix toolkit::Matrix::operator-(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
    {
        throw std::invalid_argument("Dimensões das matrizes incompatíveis para subtração.");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i)
    {
        for (int k = 0; k < cols; ++k)
        {
            result(i, k) = data[i][k] - other(i, k);
        }
    }
    return result;
}

toolkit::Matrix toolkit::Matrix::operator*(const Matrix &other) const
{
    if (cols != other.rows)
    {
        throw std::invalid_argument("Dimensões das matrizes incompatíveis para multiplicação.");
    }

    // cria uma matriz identidade para atribuir os valores do resultado
    Matrix result(rows, other.cols);

    // Realiza a multiplicação das matrizes
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < other.cols; ++j)
        {
            // Inicializa o elemento da matriz de resultado
            result(i,j) = 0;

            for (int k = 0; k < cols; ++k)
            {
                result(i, j) += data[i][k] * other(k, j);
            }
        }
    }
    return result;
}

void Matrix::showMatrix() const
{
    for (const auto &row : data)
    {
        for (const auto &value : row)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

toolkit::Matrix toolkit::Matrix::transform2dScale(float xAxisScale, float yAxisScale)
{
    std::vector<std::vector<float>> _local_transformMTX({{xAxisScale, 0.0, 0.0}, {0.0, yAxisScale, 0.0}, {0.0, 0.0, 1.0}});

    Matrix _local_MTX_Transform(_local_transformMTX);
   
    Matrix _thisMatrix(this->data);

    return _thisMatrix * _local_MTX_Transform;
}

toolkit::Matrix toolkit::Matrix::transform2dTranslate(float xAxisCoordinate, float yAxisCoordinate)
{

    std::vector<std::vector<float>> _local_transformMTX({{1.0, 0.0, xAxisCoordinate}, {0.0, 1.0, yAxisCoordinate}, {0.0, 0.0, 1.0}});

    Matrix _local_MTX_Transform(_local_transformMTX);
    Matrix _thisMatrix(this->data);

    return _thisMatrix * _local_MTX_Transform;
}

toolkit::Matrix toolkit::Matrix::transform2dRotate(float angle)
{
    std::vector<std::vector<float>> _local_transformMTX({{cos(angle), -sin(angle), 0.0}, {sin(angle), cos(angle), 0.0}, {0.0, 0.0, 1.0}});

    Matrix _local_MTX_Transform(_local_transformMTX);
    Matrix _thisMatrix(this->data);

    return _thisMatrix * _local_MTX_Transform;
}