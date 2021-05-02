#pragma once
#include "Vector.h"
class Matrix {

public:
	double** value;
	int rows;
	int columns;

	Matrix(int, int);
	~Matrix();

	Matrix& operator=(const Matrix&);
	Vector& operator*(const Vector&);

	void fillMatrixA(int, int, int);


};
