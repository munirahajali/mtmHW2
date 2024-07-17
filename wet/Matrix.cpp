#include "Matrix.h"



Matrix::Matrix(int n, int m) : n(n), m(m), matrix(new int[n * m]) 
{
    int size = n * m;
    //initiallize the matrix ("array" actually) with zeroes
    for(int i = 0; i < size; i++)
    {
        matrix[i] = 0;
    }
}

Matrix::Matrix() : n(0), m(0), matrix(nullptr)
{
    
}

Matrix::Matrix(const Matrix& other) : n(other.n), m(other.m)
{
    int size = n * m;
    matrix = new int[size];
    //copy the other matrix's values
    for(int i = 0; i < size;i++)
    {
        matrix[i] = other.matrix[i];
    }
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this == &other) //don't do anything if it's the same object
    {
        return *this;
    }
    
    delete[] matrix; //delete current array from memory
    
    n = other.n;
    m = other.m;
    int size = n * m;
    matrix = new int[size]; //create a new array for the matrix with the new size
    //copy all the values
    for(int i = 0; i < size;i++)
    {
        matrix[i] = other.matrix[i];
    }
    return *this;
}

Matrix::~Matrix()
{
    delete[] this->matrix; //free the array from memory
}


//handles invalid indices and exits the program
void handleInvalidIndices(int i, int j, int n, int m)
{
    if(i < 0 || i >= n || j < 0 || j >= m)
    {
        exitWithError(MatamErrorType::OutOfBounds);
    }
}

int& Matrix::operator()(int i, int j) //allows changing the retrieved value
{
    handleInvalidIndices(i, j, this->n, this->m);
    return matrix[i * m + j];
}

const int& Matrix::operator()(int i, int j) const //does not allow changes to the retrieved value
{   
    handleInvalidIndices(i, j, this->n, this->m);
    return matrix[i * m + j];
}


std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    for (int i = 0; i < matrix.n; ++i) //won't enter if matrix has 0 rows
    {
        if(matrix.m > 0) //won't enter if matrix has 0 columns
        {
            os << "|";
            for (int j = 0; j < matrix.m; ++j)
            {
                os << matrix(i, j) << "|";
            }
            os << std::endl;
        }
    }
    return os;
}

//handles errors when doing operations between matrices that require same rows/cols size
void handleDifferentSizes(int n1, int m1, int n2, int m2)
{
    if(n1 != n2 || m1 != m2)
    {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
}


Matrix Matrix::operator+(const Matrix& other) const
{
    handleDifferentSizes(n, m, other.n, other.m);
    Matrix newMatrix = *this; //copy current Matrix (this)
    int size = n * m;
    //add the other matrix's values to the new matrix
    for(int i = 0; i < size;i++)
    {
        newMatrix.matrix[i] += other.matrix[i];
    }
    return newMatrix;
}

Matrix Matrix::operator-(const Matrix& other) const
{
    handleDifferentSizes(n, m, other.n, other.m);
    Matrix newMatrix = *this;//copy current Matrix (this)
    int size = n * m;
    //substract the other matrix's valeus from the new matrix
    for(int i = 0; i < size;i++)
    {
        newMatrix.matrix[i] -= other.matrix[i];
    }
    return newMatrix;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    //the columns count of left side matrix must be equal to rows count of <other> matrix
    if (m != other.n) 
    {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    
    Matrix newMatrix(n, other.m); //make an empty (zero initiallized) matrix of the result size
    //algebra's matrix multiply
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < other.m; j++) 
        {
            for (int k = 0; k < m; k++) 
            {
                newMatrix(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return newMatrix;
}



Matrix& Matrix::operator+=(const Matrix& other)
{
    *this = *this + other;
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
    *this = *this - other;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
    *this = *this * other;
    return *this;
}


Matrix Matrix::operator-() const
{
    Matrix newMatrix(n, m); 
    
    int size = n * m;
    for (int i = 0; i < size; ++i) 
    {
        newMatrix.matrix[i] = -matrix[i]; 
    }
    
    return newMatrix; 
}

Matrix Matrix::operator*(int number) const
{
    Matrix newMatrix = *this; //copy the matrix
    int size = n * m;
    for(int i = 0; i < size;i++)
    {
        newMatrix.matrix[i] *= number;
    }
    return newMatrix;
}

Matrix operator*(int number, const Matrix& matrix)
{
    return matrix * number;
}

Matrix& Matrix::operator*=(int number)
{
    *this = *this * number;
    return *this;
}


bool Matrix::operator==(const Matrix& other) const
{
    if(n != other.n || m != other.m) //if not same rows and columns then obviously not equal
    {
        return false;
    }
    int size = n * m;
    for(int i = 0; i < size;i++)
    {
        //compare each value of both matrices
        if(matrix[i] != other.matrix[i])
        {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}


Matrix Matrix::rotateClockwise() const
{
    Matrix newMatrix(m, n);

    for (int i = 0; i < n; i++) 
    {
        int newColumnIndex = n - 1 - i;
        for (int j = 0; j < m; j++) 
        {
            newMatrix(j, newColumnIndex) = (*this)(i, j);
        }
    }

    return newMatrix;
}


Matrix Matrix::rotateCounterClockwise() const
{
    Matrix newMatrix(m, n); 

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            newMatrix(m - 1 - j, i) = (*this)(i, j); 
        }
    }

    return newMatrix;
}


Matrix Matrix::transpose() const
{
    Matrix newMatrix(m, n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            newMatrix(j, i) = (*this)(i, j);
        }
    }

    return newMatrix;
}

