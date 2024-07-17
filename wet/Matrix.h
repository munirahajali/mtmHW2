#pragma once

#include "Utilities.h"
#include <iostream>
class Matrix
{
    private:
        int n;
        int m;
        int *matrix;
    
    public:
        Matrix(int n, int m);
        Matrix();
        
        Matrix(const Matrix& other);
        
        Matrix& operator=(const Matrix& other);
        
        ~Matrix();
        
        int& operator()(int row, int col);  
        const int& operator()(int row, int col) const; 
        
        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
        
        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const;
        
        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(const Matrix& other);
        
        
        Matrix operator-() const;
        
        Matrix operator*(int number) const;
        friend Matrix operator*(int number, const Matrix& matrix);
        
        Matrix& operator*=(int number);
        
        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;
        
        
        Matrix rotateClockwise() const;
        Matrix rotateCounterClockwise() const;
        
        Matrix transpose() const;
};