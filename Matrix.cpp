#include <iostream>
#include "Matrix.h"
using namespace std;
Matrix::Matrix(int rows, int cols)
{
	this->rows = rows;
	this->columns = cols;
	this->value = new double* [rows];
	for (int i = 0; i < rows; i++)
	{
		value[i] = new double[cols];
		for (int j = 0; j < cols; j++)
		{
			value[i][j] = 0;
		}
	}

}
Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] value[i];
	}
	delete[] value;
}
Matrix& Matrix::operator=(const Matrix& M)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			value[i][j] = M.value[i][j];
		}
	}

	return *this;
}
Vector& Matrix::operator*(const Vector& V)
{
	Vector* newVector = new Vector(rows);
	if (columns != V.size)
	{
		cout << "Wrong size operator *" << endl;
		return *newVector;
	}

	for (int i = 0; i < rows; i++)
	{
		double sum = 0;
		for (int j = 0; j < columns; j++)
		{
			sum += value[i][j] * V.value[j];
		}
		newVector->value[i] = sum;
	}
	return *newVector;

}
void Matrix::fillMatrixA(int a1, int a2, int a3)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (i == j)
			{
				value[i][j] = a1;
			}
			else if ((i == j + 1) || (j == i + 1))
			{
				value[i][j] = a2;
			}
			else if ((i == j + 2) || (j == i + 2))
			{
				value[i][j] = a3;
			}
		}
	}

}