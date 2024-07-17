
#include "MataMvidia.h"

//copies an array (source - first <length> values) to another array (target).
void copyFramesArr(Matrix* target, Matrix* source, int length)
{
    for(int i = 0; i < length; i++)
    {
        target[i] = source[i];
    }
}

MataMvidia::MataMvidia(std::string filmName, std::string creator, Matrix* framesArr, int length)
:  filmName(filmName), creator(creator), framesArr(new Matrix[length]), length(length)
{
    //copy the array's values to the new object.
    copyFramesArr(this->framesArr, framesArr, length);
}

MataMvidia::MataMvidia(const MataMvidia& other)
    : MataMvidia(other.filmName, other.creator, other.framesArr, other.length)
{
    
}

MataMvidia& MataMvidia::operator=(const MataMvidia& other)
{
    if(this == &other) //same object, don't do anything
    {
        return *this;
    }
    
    delete[] framesArr; //delete current array from memory

    filmName = other.filmName;
    creator = other.creator;
    length = other.length;
    framesArr = new Matrix[length]; //create a new empty array of size length
    //copy the other array's values to the new array
    copyFramesArr(framesArr, other.framesArr, length);

    return *this;
}

MataMvidia::~MataMvidia()
{
    delete[] framesArr; //delete the array from memory
}

//handles invalid indices by exitting the program
void handleInvalidIndices(int i, int length)
{
    if(i < 0 || i >= length)
    {
        exitWithError(MatamErrorType::OutOfBounds);
    }
}

Matrix& MataMvidia::operator[](int i) //allows changing the retrieved value
{
    handleInvalidIndices(i, length);
    return framesArr[i];
}

const Matrix& MataMvidia::operator[](int i) const //read only basically
{
    handleInvalidIndices(i, length);
    return framesArr[i];   
}


MataMvidia& MataMvidia::operator+=(const MataMvidia& other)
{
    int newLength = length + other.length;
    Matrix* newFramesArr = new Matrix[newLength]; //create a new Matrix of the new size
    //copies first length values of framesArr to the new Matrix's array
    copyFramesArr(newFramesArr, framesArr, length);
    delete[] framesArr; //delete current array
    for(int i = 0; i < other.length;i++)
    {
        //copy the rest of the values (from other matrix)
        newFramesArr[length + i] = other[i];
    }
    //update the array and length values.
    framesArr = newFramesArr;
    length = newLength;
    return *this;
}

MataMvidia& MataMvidia::operator+=(const Matrix& matrix)
{
    //create a new array with extra cell
    Matrix* newFramesArr = new Matrix[length + 1];
    //copy first length values to the new array
    copyFramesArr(newFramesArr, framesArr, length);
    newFramesArr[length] = matrix; //add the new matrix to the end
    delete[] framesArr;
    //update both the array and the length
    framesArr = newFramesArr;
    length += 1; 
    
    return *this;
}

MataMvidia MataMvidia::operator+(const MataMvidia& other) const
{
    MataMvidia newFilm = *this;
    newFilm += other;
    return newFilm;
}


std::ostream& operator<<(std::ostream& os, const MataMvidia& other)
{
    os << "Movie Name: " << other.filmName << std::endl;
    os << "Author: " << other.creator << std::endl;
    os << std::endl;
    
    for(int i = 0 ; i < other.length;i++)
    {
        os << "Frame " << i << ":" << std::endl;
        os << other.framesArr[i]; //print the matrix using its << operator
        os << std::endl;
    }
    
    os << "-----End of Movie-----" << std::endl;
    
    return os;
}


