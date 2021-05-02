#include<math.h>
#include <iostream>
#include "Vector.h"
using namespace std;
Vector::Vector(int size)
{
	this->size = size;
	value = new double[size];
	for (int i = 0; i < size; i++)
	{
		value[i] = 0;
	}
}
Vector::~Vector()
{
	delete[] value;
}
Vector& Vector::operator-(const Vector& V)
{
	if (size != V.size)
	{
		cout << "Wrong vector size operator - " << endl;
		return *this;
	}
	for (int i = 0; i < size; i++)
	{
		value[i] -= V.value[i];
	}
	return *this;
}
Vector& Vector::operator=(const Vector& V)
{
	if (size != V.size)
	{
		cout << "Wrong vector size operator = " << endl;
		return *this;
	}
	for (int i = 0; i < size; i++)
	{
		value[i] = V.value[i];
	}
	return *this;
}
double Vector::normVect()
{
	double norm = 0;
	for (int i = 0; i < size; i++)
	{
		norm += value[i] * value[i];
	}
	return sqrt(norm);

}
void Vector::fillVectorB(int f)
{
	for (int i = 0; i < size; i++)
	{
		value[i] = sin(i * (f + 1));
	}
}
void Vector::fillWithZeros()
{
	for (int i = 0; i < size; i++)
	{
		value[i] = 0;
	}
}