#ifndef MVECTOR_H
#define MVECTOR_H

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

template <class T> // allows us to use multiple data types with functions
class mVector {
    public:
        // FUNCTIONS:
        mVector(); // constructor
        mVector(int dims); // constructor specifying num of dimensions
        mVector(std::vector<T> input); // constructor with input data
        ~mVector(); // destructor
        int getDims() const; // function to return number of vector dimensions
        void setElement(int index, T value); // function to set element at index;
        T getElement(int index) const; // function to return element at index
        T getNorm(); // function to calculate vector length, e.g. sqrt((v_1)^2 + (v_2)^2 + ... + (v_n)^2)
        mVector<T> getNormalizedCopy(); // function to return a normalized copy of the vector, e.g. v / v.getNorm()
        void normalize(); // function to normalize the vector in place, e.g. v = v.getNormalizedCopy() but with same pos
        mVector<T> operator+ (const mVector<T> &v) const; // overload addition operator
        mVector<T> operator- (const mVector<T> &v) const; // overload subtraction operator
        mVector<T> operator* (const T &c) const; // overload product with constant operator
        template <class U> friend mVector<U> operator* (const U& c, const mVector<U>& v); // friend to product overload
        static T dot(const mVector<T>& a, const mVector<T>& b); // function to compute the dot product, e.g. a_1b_1 + a_2b_2 + ... + a_nb_n
        static mVector<T> cross(const mVector<T>& a, const mVector<T>& b); // function to compute the cross product, e.g. find formal determinant
    
    private:
        // VARIABLES:
        std::vector<T> vectorData; // data contained in vector
        int vectorDims; // vector dimensions, e.g. size of vector
};

// constructor
template <class T>
mVector<T>::mVector() {
    vectorData = std::vector<T>();
    vectorDims = 0;
}

// constructor specifying num of dimensions
template <class T>
mVector<T>::mVector(int dims) {
    vectorData = std::vector<T>(dims, static_cast<T>(0.0));
    vectorDims = dims;
}

// constructor with input data
template <class T>
mVector<T>::mVector(std::vector<T> input) {
    vectorData = input;
    vectorDims = input.size();
}

// destructor
template <class T>
mVector<T>::~mVector() {}

// function to return number of vector dimensions
template <class T>
int mVector<T>::getDims() const {
    return vectorDims;
}

// function to set element at index
template <class T>
void mVector<T>::setElement(int index, T value) {
    vectorData[index] = value;
}

// function to return element at index
template <class T>
T mVector<T>::getElement(int index) const {
    return vectorData[index];
}

// function to calculate vector length, e.g. sqrt((v_1)^2 + (v_2)^2 + ... + (v_n)^2)
template <class T>
T mVector<T>::getNorm() {
    T norm = static_cast<T>(0.0);
    for(int i = 0; i < vectorDims; i++)
        norm += (vectorData[i] * vectorData[i]); // computing the sum from start to n of (v_n)^2
    return sqrt(norm); // find sqrt of result and return it
}

// function to return a normalized copy of the vector, e.g. v / v.getNorm()
template <class T>
mVector<T> mVector<T>::getNormalizedCopy() {
    T norm = this->getNorm(); // v.getNorm()
    mVector<T> normCopy(vectorData); // copy of v
    return normCopy * (static_cast<T>(1.0) / norm); // v / v.getNorm()
}

// function to normalize the vector in place, e.g. v = v.getNormalizedCopy() but with same pos
template <class T>
void mVector<T>::normalize() {
    T norm = this->getNorm();
    for(int i = 0; i < vectorDims; i++) // change vector data value by value to keep in place while normalizing
        vectorData[i] = vectorData[i] * (static_cast<T>(1.0) / norm);
}

// overload addition operator
template <class T>
mVector<T> mVector<T>::operator+ (const mVector<T>& v) const {
    if(vectorDims != v.vectorDims) // verifying that vectors are same size
        throw std::invalid_argument("vector dimensions must be equal to perform addition");
    std::vector<T> sumData;
    for(int i = 0; i < vectorDims; i++)
        sumData.push_back(vectorData[i] + v.vectorData[i]);
    mVector<T> sum(sumData);
    return sum;
}

// overload subtraction operator
template <class T>
mVector<T> mVector<T>::operator- (const mVector<T>& v) const {
    if(vectorDims != v.vectorDims) // verifying that vectors are same size
        throw std::invalid_argument("vector dimensions must be equal to perform subtraction");
    std::vector<T> diffData;
    for(int i = 0; i < vectorDims; i++)
        diffData.push_back(vectorData[i] - v.vectorData[i]);
    mVector<T> diff(diffData);
    return diff;
}

// overload product with constant operator
template <class T>
mVector<T> mVector<T>::operator* (const T& c) const {
    std::vector<T> productData;
    for(int i = 0; i < vectorDims; i++)
        productData.push_back(vectorData[i] * c);
    mVector<T> product(productData);
    return product;
}

// friend to product overload
template <class T>
mVector<T> operator* (const T& c, const mVector<T>& v) {
    std::vector<T> productData;
    for(int i = 0; i < v.vectorDims; i++)
        productData.push_back(v.vectorData[i] * c);
    mVector<T> product(productData);
    return product;
}

// function to compute the dot product, e.g. a_1b_1 + a_2b_2 + ... + a_nb_n
template <class T>
T mVector<T>::dot(const mVector<T>& a, const mVector<T>& b) {
    if(a.vectorDims != b.vectorDims) // verifying that vectors are same size
        throw std::invalid_argument("vector dimensions must be equal to perform dot product");
    T dotProduct = static_cast<T>(0.0);
    for(int i = 0; i < a.vectorDims; i++)
        dotProduct += a.vectorData[i] * b.vectorData[i];
    return dotProduct;
}

// function to compute the cross product, e.g. find formal determinant
template <class T>
mVector<T> mVector<T>::cross(const mVector<T>& a, const mVector<T>& b) {
    if(a.vectorDims != b.vectorDims && a.vectorDims != 3) // verifying that vectors are same size with three dimensions
        throw std::invalid_argument("vector dimensions must be equal to 3 to perform cross product");
    // below is the cross product defined only for three dimensions
    // this is done by calculating the formal determinant for a square 3x3 matrix (?)
    std::vector<T> crossData;
    crossData.push_back((a.vectorData[1] * b.vectorData[2]) - (a.vectorData[2] * b.vectorData[1]));
	crossData.push_back(-((a.vectorData[0] * b.vectorData[2]) - (a.vectorData[2] * b.vectorData[0])));
	crossData.push_back((a.vectorData[0] * b.vectorData[1]) - (a.vectorData[1] * b.vectorData[0]));
    mVector<T> crossResult(crossData);
    return crossResult;
}

#endif