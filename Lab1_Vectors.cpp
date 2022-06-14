#include <iostream>
#include <math.h>
#include <initializer_list>
#include "m_vector.h"
#include "Tests.h"

#define VALL 15;

int main()
{
    m_vector <double> vector1 = checkInitializer_listCreating();
    m_vector <double> vector2 = checkSizeCreating();

    std::cout << "checking 'print' for Initializer_listCreating: " << "\n";
    vector1.print();
    vector1.print_type();
    std::cout << "size of vector1: " << vector1.get_size() << "\n";
    std::cout << "length of vector1: " << vector1.get_length() << "\n";

    std::cout << "\nchecking 'print' for SizeCreating: " << "\n";
    vector2.print();
    vector2.print_type();
    std::cout << "size of vector2: " << vector2.get_size() << "\n";
    std::cout << "length of vector2: " << vector2.get_length() << "\n";
    double val = VALL;
    cout << "\nchecking 'set_elem' for Initializer_listCreating: \n";
    checkSetOK(vector1, val);
    checkSetError(vector1, val);

    cout << "\nchecking 'get_elem' for Initializer_listCreating: \n";
    checkGetOK(vector1);
    checkGetError(vector1);
    
    cout << "\nchecking '+': \n";
    m_vector <double> vectorAddendum { 1,1,1,1,1};
    checkSumm(vector1, vectorAddendum);
    checkSummError(vector1, vector2);
    
    cout << "\nchecking '-': \n";
    vector1 = checkSubInNewVectorOK();
    vector1 = checkSubInNewVectorError();
   
    cout << "\nchecking '*': \n";
    vector1 = checkMultInNewVectorOK();

    cout << "\nchecking '/': \n";
    vector1 = checkDivInNewVectorOK();
    
    cout << "\nchecking '+' operations: \n";
    m_vector <double> vector3(vector1); //проверка оператора копирования с нулевым вектором
    std::cout << "OK: " << "vector3 = vector1: " << vector3;
        
    vector2 = vector1; //проверка перегрузки оператора присваивания
    cout << "\nchecking '=': \n" << "OK: " << vector2;

    cout << "\nchecking '<<': \n" << "OK: ";
    std::cout << "vector2: " << vector2;
    std::cout << "vector1: " << vector1;

    cout << "\nchecking '+=': \n";
    checkingAdditionInOldVectorOK();
    checkingAdditionInOldVectorError();

    cout << "\nchecking '-=': \n";
    checkSubtractionInOldVectorOK();
    checkSubtractionInOldVectorError();

    cout << "\nchecking '*=': \n";
    checkMultiplicationInOldVectorOK();

    cout << "\nchecking '/=': \n";
    checkDivisionInOldVectorOK();
    checkDivisionInOldVectorError();

    cout << "\nchecking Array: \n";
    checkArrayOK();
}

m_vector <double> checkInitializer_listCreating()
{
    std::cout << "creating with initialisation:\n";
    m_vector <double> vec{ 1,2,3,4,5 };
    std::cout << vec;
    std::cout << "\n";
    return vec;    
}

m_vector <double> checkSizeCreating()
{
    std::cout << "creating with only size:\n";
    m_vector <double> vec(3);
    std::cout << vec;
    std::cout << "\n";
    return vec; 
}

m_vector <double> checkSumm(m_vector <double>& vector1, m_vector <double>& vector2)
{    
    try {
        m_vector <double> vec(vector1 + vector2);
        std::cout << "OK: +:" << vec;
        return vec;
    }
    catch (invalid_argument& in_ar) {
        std::cout << in_ar.what() << "\n";
    }
}

m_vector <double> checkSummError(m_vector <double>& vector1, m_vector <double>& vector2)
{
    m_vector <double> vec = checkSumm(vector1, vector2);
    return vec;
}

m_vector <double> checkSub(m_vector <double>& vector1, m_vector <double>& vector2)
{    
    try {
        m_vector <double> vec(vector1 - vector2);
        std::cout << "OK: -:" << vec;
        return vec;
    }
    catch (invalid_argument& in_ar) {
        std::cout << in_ar.what() << "\n";
    }
}

m_vector <double> checkSubInNewVectorOK()
{
    m_vector <double> vector1{ 1,2,3,4 };
    m_vector <double> vector2{ 1,2,3,4 };
    m_vector <double> vec = checkSub(vector1, vector2);
    return vec;
}

m_vector <double> checkSubInNewVectorError()
{
    m_vector <double> vector1{ 1,2,3,4 };
    m_vector <double> vector2{ 1,2,3 };
    m_vector <double> vec = checkSub(vector1, vector2);
    return vec;
}

m_vector <double> checkMult(m_vector <double>& vector1, double var)
{
    try {
        m_vector <double> vec(vector1 * var);
        std::cout << "OK: *:" << vec;
        return vec;
    }
    catch (invalid_argument& in_ar) {
        std::cout << in_ar.what() << "\n";
    }
}

m_vector <double> checkMultInNewVectorOK()
{
    m_vector <double> vector1{ 1,2,3,4 };
    m_vector <double> vec = checkMult(vector1, 2.3);
    return vec;
}

m_vector <double> checkDiv(m_vector <double>& vector1, double var)
{
    try {
        m_vector <double> vec(vector1 / var);
        cout << "OK: /: " << vec;
        return vec;
    }
    catch (invalid_argument& in_ar) {
        std::cout << in_ar.what() << "\n";
    }
}

m_vector <double> checkDivInNewVectorOK()
{
    m_vector <double> vector1{ 1,2,3,4 };
    m_vector <double> vec = checkDiv(vector1, 5);
    return vec;
}

m_vector <double> checkDivInNewVectorError()
{
    m_vector <double> vector1{ 1,2,3,4 };
    m_vector <double> vec = checkDiv(vector1, 0);
    return vec;
}

void checkSet(m_vector <double> vec, int index, double elem)
{    
    try {
        vec.set_elem(index, elem);
        std::cout << "OK: set_elem:" << vec;
    }
    catch (invalid_argument& in_ar) {
        std::cout << in_ar.what() << "\n";
    }
}

void checkSetOK(m_vector <double> vector, double val)
{    
    checkSet(vector, 1, val);
}

void checkSetError(m_vector <double> vector, double val)
{
    checkSet(vector, 15, val);
}

void checkGet(m_vector <double> vec, int index)
{
    try {
        std::cout << "OK: get_elem: vec[" << index << "]: " << vec.get_elem(index) << "\n";
    }
    catch (invalid_argument& in_ar) {
        std::cout << in_ar.what() << "\n";
    }
}

void checkGetOK(m_vector <double> vector)
{
    checkGet(vector, 1);
}

void checkGetError(m_vector <double> vector)
{
    checkGet(vector, 15);
}

void checkAddition(m_vector <double> vector1, m_vector <double> vector2)
{
    cout << "OK: " << "+=: \n";
    try {
        vector1 += vector2;
        std::cout << vector1;
    }
    catch (invalid_argument& in_ar) {
        std::cout << in_ar.what() << "\n";
    }
}

void checkingAdditionInOldVectorOK()
{
    m_vector <double> vector1{ 1,2,3,4 };
    m_vector <double> vector2{ 1,2,3,4 };
    checkAddition(vector1, vector2);
}

void checkingAdditionInOldVectorError()
{
    m_vector <double> vector1{ 1,2,3,4 };
    m_vector <double> vector2{ 1,2,3 };
    checkAddition(vector1, vector2);
}

void checkSubtraction(m_vector <double> vector1, m_vector <double> vector2)
{
    cout << "OK: " << "-=: \n";
    try {
        vector1 -= vector2;
        std::cout << vector1;
    }
    catch (invalid_argument& in_ar) {
        std::cout << in_ar.what() << "\n";
    }
}

void checkSubtractionInOldVectorOK()
{
    m_vector <double> vector1{ 1,2,3,4 };
    m_vector <double> vector2{ 1,2,3,4 };
    checkSubtraction(vector1, vector2);
}

void checkSubtractionInOldVectorError()
{
    m_vector <double> vector1{ 1,2,3,4 };
    m_vector <double> vector2{ 1,2,3 };
    checkSubtraction(vector1, vector2);
}

void checkMultiplication(m_vector <double> vec, double num)
{
   try {
        vec *= num;
        cout << "OK: *=: \n";
        std::cout << vec;
    }
    catch (invalid_argument& in_ar) {
        std::cout << in_ar.what() << "\n";
    }
}

void checkMultiplicationInOldVectorOK()
{
    m_vector <double> vector1{ 1,2,3,4 };
    checkMultiplication(vector1, 5);
}

void checkDivision(m_vector <double> vec, double num)
{
    try {
        vec /= num;
        cout << "OK: /=: \n";
        std::cout << vec;
    }
    catch (invalid_argument& in_ar) {
        std::cout << in_ar.what() << "\n";
    }
}

void checkDivisionInOldVectorOK()
{
    m_vector <double> vector1{ 1,2,3,4 };
    checkDivision(vector1, 5);
}

void checkDivisionInOldVectorError()
{
    m_vector <double> vector1{ 1,2,3,4 };
    checkDivision(vector1, 0);
}

void checkSquareBrackets(m_vector <double> vec, int index)
{
    try {
        std::cout << "checkSquareBrackets: vec[" << index << "]: " << vec[index];
    }
    catch (invalid_argument& in_ar) {
        std::cout << in_ar.what() << "\n";
    }
}

void checkArray(m_vector <double> vec)
{
    double* arr = (double*)malloc(sizeof(double) * 3);
    arr = vec.to_array();
    cout << "OK: \n";
    for (int i = 0; i < 3; i++)
        cout << "\n" << "arr[" << i << "]: " << arr[i];
}

void checkArrayOK()
{
    m_vector <double> vector1{ 1,2,3,4 };
    checkArray(vector1);
}

void checkGet_elem (m_vector <double> vec, int num)
{
    try
    {
        double val = vec[num];
        cout << "OK: get_elem: val=" << val << "\n";
    }
    catch (invalid_argument& in_ar) {
        std::cout << in_ar.what() << "\n";
    }
}

void checkGet_elemOK(m_vector <double>& vector)
{
    checkGet_elem(vector, 2);
}

void checkGet_elemError(m_vector <double>& vector)
{
    checkGet_elem (vector, 15);
}
