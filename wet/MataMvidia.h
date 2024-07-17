#pragma once

#include "MataMvidia.h"
#include "Matrix.h"
class MataMvidia
{
    private:
        std::string filmName;
        std::string creator;
        Matrix *framesArr;
        int length;
        
    public:
        
        MataMvidia(std::string filmName, std::string creator, Matrix* framesArr, int length);
        
        MataMvidia(const MataMvidia& other);

        MataMvidia& operator=(const MataMvidia& other);
    
        ~MataMvidia();
        
        Matrix& operator[](int i);
        const Matrix& operator[](int i) const;
        
        MataMvidia& operator+=(const MataMvidia& other);
        MataMvidia& operator+=(const Matrix& matrix);
         MataMvidia operator+(const MataMvidia& other) const;
        
        friend std::ostream& operator<<(std::ostream& os, const MataMvidia& other);

};