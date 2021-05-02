#pragma once
class Vector {

public:
	double* value;
	int size;

	Vector(int);
	~Vector();

	Vector& operator-(const Vector&);
	Vector& operator=(const Vector&);

	void fillVectorB(int);
	void fillWithZeros();
	double normVect();

};