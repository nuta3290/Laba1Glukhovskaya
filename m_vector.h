#pragma once
#include <iostream>
#include <math.h>
#include <initializer_list>

using namespace std;


template<typename T>
class m_vector
{
private:
	int size;
	//  double length;
	T* data;

public:
	class Iterator
	{
	private:
		T* current_pos;
		T* begin;
		T* end;
		int size;
	public:
		Iterator(m_vector<T>& obj) //    �����������, ����������� ������ ������������� ������, ������� ���������� ������ � ������� ������� ���������
		{
			this->begin = &obj.data;
			this->end = begin + obj.size * sizeof(T);
			this->current_pos = begin;
			this->size = obj.size;
		};

		T value() // �������� �������� �������� ������� � ����������
		{
			return *this->current_pos;
		};

		template<typename T>
		Iterator next() // ������� � ���������� ������� � ����������
		{
			this->current_pos += sizeof(T);
			return this;
		};

		bool is_end() // ��������� �� �������� �� �������� ��������� ������� ����������, ��������� �� ��������� ��������.����� ��� ����������� ����� ������������
		{
			return (this->current_pos >= end);
		};

		Iterator& operator++() // ���������� ���������, ������������ next()
		{
			this->current_pos += sizeof(T);
			return this;
		};

		T& operator*() // �������� �������������, ������������ value()
		{
			return *this->current_pos;
		};

		bool operator==(Iterator& b) // �������� ���������
		{
			return (*this->current_pos == *(b));
		};
	};

	friend class Iterator;

	m_vector(int size); // ����������� � ��������� �����������

	~m_vector(); // ����������

	explicit m_vector(std::initializer_list<T> lst); // ����������� �� ������� �������������

	double get_size(); // �������� ������� �����������

	double get_length(); // �������� ������� ������ (�����)

	m_vector(const m_vector<T>& other); // ����������� �����������

	m_vector<T>& operator= (m_vector<T> other); //���������� ��������� = ������������
	
	void set_elem(int index, T& elem); // �������� ������� ������� �� �������

	T& get_elem(int index); // �������� ������� ������ �� �������

	T* to_array(); // ������� ����� ������, � ������� �������� ��� �������� �������.

	T& operator[](int index); // ������ � ��������, ���������� �������.
	
	template<typename _T>
	friend ostream& operator<<(std::ostream& os, m_vector<_T>& lst); // ���������� ��������� << ��� ������ ������ � �����(cout � �������)

	m_vector<T>& operator+=(m_vector<T>& other); // ���������� ��������� +=, � this ���������� vect.

	m_vector<T>& operator-=(m_vector<T>& other); // ���������� ��������� -=, �� this ���������� vect.
	
	m_vector<T>& operator*=(T& val); // ���������� ��������� *=, ������ ������� this ����������� �� val.
	
	m_vector<T>& operator/=(T& val); // ���������� ��������� /=, ������ ������� this ������� �� val.
	
	template<typename _T>
	friend m_vector<_T> operator+(m_vector<_T>& v1, m_vector<_T>& v2); // ���������� ��������� + � v1 ���������� v2.

	template<typename _T>
	friend m_vector<_T> operator-(m_vector<_T>& v1, m_vector<_T>& v2); //���������� ��������� - , �� v1 ���������� v2.

	
	void print();

	void print_type(); // �������� ���
	Iterator iterator_begin(); // ����� ��������� ��������� �� ������ ������� (������ �������).

	Iterator iterator_end(); // ����� ��������� ��������� �� ����� ������ (��������� �������, ��������� �� ���������
};








template<typename T>
m_vector<T>::m_vector(int size) // ����������� � ��������� �����������
{
	this->size = size;
	this->data = new T[size];
	for (int i = 0; i < size; i++) {
		this->data[i] = 0;
	}
};

template<typename T>
m_vector<T>::~m_vector() // ����������
{
	if (this->data != NULL)
		delete[] data;
};

template<typename T>
m_vector<T>::m_vector(std::initializer_list<T> lst) // ����������� �� ������� �������������
{
	this->size = lst.size();
	T* tmp = new T[size];
	int j = 0;
	for (auto i = lst.begin(); i != lst.end(); i++, j++) {
		tmp[j] = *i;
	}
	this->data = tmp;
};

template<typename T>
double m_vector<T>::get_size() // �������� ������� �����������
{
	return this->size;
};

template<typename T>
double m_vector<T>::get_length() // �������� ������� ������ (�����)
{
	double length = 0;
	for (int i = 0; i < this->size; i++)
		length += this->data[i] * this->data[i];
	return sqrt(length);
};

template<typename T>
m_vector<T>::m_vector(const m_vector<T>& other) // ����������� �����������
{
	this->size = other.size;
	this->data = new T[other.size];
	for (auto i = 0; i < other.size; i++)
		this->data[i] = other.data[i];
};



template<typename T>
void m_vector<T>::set_elem(int index, T& elem) // �������� ������� ������� �� �������
{
	if (index < size && index>0)
		this->data[index] = elem;
	else
		throw invalid_argument("ERROR:set_elem: index out of range");
};

template<typename T>
T& m_vector<T>::get_elem(int index) // �������� ������� ������ �� �������
{
	if (index < size && index>0)
		return this->data[index];
	else
		throw invalid_argument("ERROR: get_elem: index out of range");
};

template<typename T>
T* m_vector<T>::to_array() // ������� ����� ������, � ������� �������� ��� �������� �������.
{
	T* array = new T[this->size];
	for (int i = 0; i < this->size; i++)
		array[i] = this->data[i];
	return array;
};







template<typename _T>
ostream& operator<<(std::ostream& os, m_vector<_T>& lst) // ���������� ��������� << ��� ������ ������ � �����(cout � �������)
{
	os << "size: " << lst.size << endl;
	for (int i = 0; i < lst.size; i++) {
		os << "data[" << i << "]: " << lst.data[i] << endl;
	}
	return os;
};

template<typename _T>
m_vector<_T>& m_vector<_T>::operator+=(m_vector<_T>& other) // ���������� ��������� +=, � this ���������� vect.
{
	if (this->size == other.size) {
		for (auto i = 0; i < other.size; i++)
			this->data[i] = other.data[i] + this->data[i];
	}
	else
		throw invalid_argument("ERROR: +=: operation wasn't done: different size");
	return *this;
};

template<typename _T>
m_vector<_T>& m_vector<_T>::operator-=(m_vector<_T>& other) // ���������� ��������� -=, �� this ���������� vect.
{
	if (this->size == other.size) {
		for (auto i = 0; i < other.size; i++)
			this->data[i] = other.data[i] - this->data[i];
	}
	else
		throw invalid_argument("ERROR: -=: operation wasn't done: different size");
	return *this;
};

template<typename _T>
m_vector<_T> operator+(m_vector<_T>& v1, m_vector<_T>& v2) // ���������� ��������� + � v1 ���������� v2.
{
	m_vector <_T> v3(v1.size);
	if (v1.size == v2.size) {
		for (auto i = 0; i < v1.size; i++)
			v3.data[i] = v2.data[i] + v1.data[i];
	}
	else
		throw invalid_argument("ERROR: +: operation wasn't done: different size");
	return v3;
};

template<typename T>
T& m_vector<T>::operator[](int index) // ������ � ��������, ���������� �������.
{
	return get_elem(index);
};

template<typename _T>
m_vector<_T> operator-(m_vector<_T>& v1, m_vector<_T>& v2) //���������� ��������� - , �� v1 ���������� v2.
{
	m_vector <_T> v3(v1.size);
	if (v1.size == v2.size) {
		for (auto i = 0; i < v1.size; i++)
			v3.data[i] = v2.data[i] - v1.data[i];
	}
	else
		throw invalid_argument("ERROR: -: operation wasn't done: different size");
	return v3;
};

template<typename _T>
m_vector<_T> operator*(m_vector<_T>& v1, _T& val) //���������� ���������*, ������ ������� v1 ����������� �� val.
{
	m_vector<_T> copy = v1;
	for (size_t i = 0; i < copy.size(); i++)
		copy[i] = copy[i] * val;
	return copy;
};

template<typename _T>
m_vector<_T> operator /(m_vector<_T>& v1, _T& val) // ���������� ��������� / , ������ ������� v1 ������� �� val.
{
	return v1 /= val;
}

template<typename T>
void m_vector<T>::print()
{
	for (int i = 0; i < size; i++)
		cout << data[i] << endl;
};

template<typename T>
void m_vector<T>::print_type()// �������� ���
{
	cout << "Type is " << typeid(*this).name() << endl;
};

