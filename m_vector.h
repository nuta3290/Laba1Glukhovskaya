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
		Iterator(m_vector<T>& obj) //    конструктор, принимающий объект контейнерного класса, который необходимо обойти с помощью данного итератора
		{
			this->begin = &obj.data;
			this->end = begin + obj.size * sizeof(T);
			this->current_pos = begin;
			this->size = obj.size;
		};

		T value() // получить значение текущего объекта в контейнере
		{
			return *this->current_pos;
		};

		template<typename T>
		Iterator next() // перейти к следующему объекту в контейнере
		{
			this->current_pos += sizeof(T);
			return this;
		};

		bool is_end() // указывает ли итератор на конечный фиктивный элемент контейнера, следующий за последним реальным.Нужен для определения конца итерирования
		{
			return (this->current_pos >= end);
		};

		Iterator& operator++() // префиксный инкремент, эквивалентен next()
		{
			this->current_pos += sizeof(T);
			return this;
		};

		T& operator*() // оператор разыменования, эквивалентен value()
		{
			return *this->current_pos;
		};

		bool operator==(Iterator& b) // оператор сравнения
		{
			return (*this->current_pos == *(b));
		};
	};

	friend class Iterator;

	m_vector(int size); // конструктор с указанием размерности

	~m_vector(); // деструктор

	explicit m_vector(std::initializer_list<T> lst); // конструктор со списком инициализации

	double get_size(); // получить текущую размерность

	double get_length(); // получить текущий размер (длину)

	m_vector(const m_vector<T>& other); // конструктор копирования

	m_vector<T>& operator= (m_vector<T> other); //перегрузка оператора = присваивания
	
	void set_elem(int index, T& elem); // изменить элемент вектора по индексу

	T& get_elem(int index); // получить элемент списка по индексу

	T* to_array(); // создать новый массив, в который записать все элементы вектора.

	T& operator[](int index); // доступ к элементу, аналогично массиву.
	
	template<typename _T>
	friend ostream& operator<<(std::ostream& os, m_vector<_T>& lst); // перегрузка оператора << для вывода класса в поток(cout к примеру)

	m_vector<T>& operator+=(m_vector<T>& other); // перегрузка оператора +=, к this добавлется vect.

	m_vector<T>& operator-=(m_vector<T>& other); // перегрузка оператора -=, из this вычитается vect.
	
	m_vector<T>& operator*=(T& val); // перегрузка оператора *=, каждый элемент this домножается на val.
	
	m_vector<T>& operator/=(T& val); // перегрузка оператора /=, каждый элемент this делится на val.
	
	template<typename _T>
	friend m_vector<_T> operator+(m_vector<_T>& v1, m_vector<_T>& v2); // перегрузка оператора + к v1 добавлется v2.

	template<typename _T>
	friend m_vector<_T> operator-(m_vector<_T>& v1, m_vector<_T>& v2); //перегрузка оператора - , из v1 вычитается v2.

	
	void print();

	void print_type(); // печатать тип
	Iterator iterator_begin(); // метод получения итератора на начало вектора (первый элемент).

	Iterator iterator_end(); // метод получения итератора на конец списка (фиктивный элемент, следующий за последним
};








template<typename T>
m_vector<T>::m_vector(int size) // конструктор с указанием размерности
{
	this->size = size;
	this->data = new T[size];
	for (int i = 0; i < size; i++) {
		this->data[i] = 0;
	}
};

template<typename T>
m_vector<T>::~m_vector() // деструктор
{
	if (this->data != NULL)
		delete[] data;
};

template<typename T>
m_vector<T>::m_vector(std::initializer_list<T> lst) // конструктор со списком инициализации
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
double m_vector<T>::get_size() // получить текущую размерность
{
	return this->size;
};

template<typename T>
double m_vector<T>::get_length() // получить текущий размер (длину)
{
	double length = 0;
	for (int i = 0; i < this->size; i++)
		length += this->data[i] * this->data[i];
	return sqrt(length);
};

template<typename T>
m_vector<T>::m_vector(const m_vector<T>& other) // конструктор копирования
{
	this->size = other.size;
	this->data = new T[other.size];
	for (auto i = 0; i < other.size; i++)
		this->data[i] = other.data[i];
};



template<typename T>
void m_vector<T>::set_elem(int index, T& elem) // изменить элемент вектора по индексу
{
	if (index < size && index>0)
		this->data[index] = elem;
	else
		throw invalid_argument("ERROR:set_elem: index out of range");
};

template<typename T>
T& m_vector<T>::get_elem(int index) // получить элемент списка по индексу
{
	if (index < size && index>0)
		return this->data[index];
	else
		throw invalid_argument("ERROR: get_elem: index out of range");
};

template<typename T>
T* m_vector<T>::to_array() // создать новый массив, в который записать все элементы вектора.
{
	T* array = new T[this->size];
	for (int i = 0; i < this->size; i++)
		array[i] = this->data[i];
	return array;
};







template<typename _T>
ostream& operator<<(std::ostream& os, m_vector<_T>& lst) // перегрузка оператора << для вывода класса в поток(cout к примеру)
{
	os << "size: " << lst.size << endl;
	for (int i = 0; i < lst.size; i++) {
		os << "data[" << i << "]: " << lst.data[i] << endl;
	}
	return os;
};

template<typename _T>
m_vector<_T>& m_vector<_T>::operator+=(m_vector<_T>& other) // перегрузка оператора +=, к this добавлется vect.
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
m_vector<_T>& m_vector<_T>::operator-=(m_vector<_T>& other) // перегрузка оператора -=, из this вычитается vect.
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
m_vector<_T> operator+(m_vector<_T>& v1, m_vector<_T>& v2) // перегрузка оператора + к v1 добавлется v2.
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
T& m_vector<T>::operator[](int index) // доступ к элементу, аналогично массиву.
{
	return get_elem(index);
};

template<typename _T>
m_vector<_T> operator-(m_vector<_T>& v1, m_vector<_T>& v2) //перегрузка оператора - , из v1 вычитается v2.
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
m_vector<_T> operator*(m_vector<_T>& v1, _T& val) //перегрузка оператора*, каждый элемент v1 домножается на val.
{
	m_vector<_T> copy = v1;
	for (size_t i = 0; i < copy.size(); i++)
		copy[i] = copy[i] * val;
	return copy;
};

template<typename _T>
m_vector<_T> operator /(m_vector<_T>& v1, _T& val) // перегрузка оператора / , каждый элемент v1 делится на val.
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
void m_vector<T>::print_type()// печатать тип
{
	cout << "Type is " << typeid(*this).name() << endl;
};

