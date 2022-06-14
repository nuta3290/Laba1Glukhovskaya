#pragma once
#include "m_vector.h"

m_vector <double> checkInitializer_listCreating();
m_vector <double> checkSizeCreating();

void checkGet_elem(m_vector <double> vec, int index);
void checkGet_elemOK(m_vector <double>& vector);
void checkGet_elemError(m_vector <double>& vector);

void checkSet(m_vector <double> vector, int index, double elem);
void checkSetOK(m_vector <double> vector, double val);
void checkSetError(m_vector <double> vector, double elem);

void checkGet(m_vector <double> vector, int index);
void checkGetOK(m_vector <double> vector);
void checkGetError(m_vector <double> vector);

m_vector <double> checkSumm(m_vector <double>& vector1, m_vector <double>& vector2);
m_vector <double> checkSummOK(m_vector <double>& vector1, m_vector <double>& vector2);
m_vector <double> checkSummError(m_vector <double>& vector1, m_vector <double>& vector2);
m_vector <double> checkSubInNewVectorOK();
m_vector <double> checkSubInNewVectorError();
m_vector <double> checkMultInNewVectorOK();
m_vector <double> checkDivInNewVectorOK();
m_vector <double> checkDivInNewVectorError();
m_vector <double> checkSub(m_vector <double>& vector1, m_vector <double>& vector2);
m_vector <double> checkDiv(m_vector <double>& vector1, double var);
m_vector <double> checkMult(m_vector <double>& vector1, double var);
void checkingAdditionInOldVectorOK();
void checkingAdditionInOldVectorError();
void checkSubtractionInOldVectorOK();
void checkSubtractionInOldVectorError();
void checkMultiplicationInOldVectorOK();
void checkDivisionInOldVectorOK();
void checkDivisionInOldVectorError();
void checkMultiplication(m_vector <double> vec, double num);
void checkDivision(m_vector <double> vec, double num);



void checkArray(m_vector <double> vector);
void checkArrayOK();