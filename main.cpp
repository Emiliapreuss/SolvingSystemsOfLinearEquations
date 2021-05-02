#include <iostream>
#include <ctime> 
#include "Matrix.h"

#define INDEKS 180157
#define N 957
#define a1A 6
#define a1C 3
#define a2 -1
#define a3 -1
#define EPSILON 1e-9
using namespace std;

int Jacobi(Matrix* A, Vector* b, Vector* x, int n);
int GaussSeidel(Matrix* A, Vector* b, Vector* x, int n);
double LU(Matrix* A, Vector* b, Vector* x, int n);
int main()
{
	//zadB
	cout << "ZADANIE B" << endl;
	Matrix A(N, N);
	Vector b(N);
	Vector x(N);
	A.fillMatrixA(a1A, a2, a3);
	b.fillVectorB(0);

	clock_t start, stop;
	start = clock();
	int iterationsJacobi1 = Jacobi(&A, &b, &x, N);
	stop = clock();
	double time = (stop - start) / (double)CLOCKS_PER_SEC;
	cout << "Metoda Jacobiego liczba iteracji: " << iterationsJacobi1 << " czas trwania: " << time << "s" << endl;
	x.fillWithZeros();
	start = clock();
	int iterationsGaussSeidel1 = GaussSeidel(&A, &b, &x, N);
	stop = clock();
	time = (stop - start) / (double)CLOCKS_PER_SEC;
	cout << "Metoda Gaussa-Seidla liczba iteracji: " << iterationsGaussSeidel1 << " czas trwania: " << time << "s" << endl;


	//zadC
	cout << "**************************************************" << endl << endl << "ZADANIE C" << endl;
	A.fillMatrixA(a1C, a2, a3);
	x.fillWithZeros();

	int iterationsJacobi2 = Jacobi(&A, &b, &x, N);
	if (iterationsJacobi2 != -1)
	{
		cout << "Metoda Jacobiego zbiega sie, liczba iteracji: " << iterationsJacobi2 << endl;
	}
	else
	{
		cout << " Metoda Jacobiego nie zbiega sie" << endl;
	}
	x.fillWithZeros();
	int iterationsGaussSeidel2 = GaussSeidel(&A, &b, &x, N);
	if (iterationsGaussSeidel2 != -1)
	{
		cout << " Metoda Gaussa-Seidla zbiega sie, liczba iteracji: " << iterationsGaussSeidel1 << endl;
	}
	else
	{
		cout << " Metoda Gaussa-Seidla nie zbiega sie " << endl;
	}
	cout << "**************************************************" << endl << endl << "ZADANIE D" << endl;
	//zadD
	x.fillWithZeros();
	start = clock();
	double norm = LU(&A, &b, &x, N);
	stop = clock();
	time = (stop - start) / (double)CLOCKS_PER_SEC;
	cout << "Norma z wektora residuum dla metody LU " << norm << " czas trwania " << time << "s" << endl;

	//zadE
	cout << "**************************************************" << endl << endl << "ZADANIE E" << endl;
	int n[6] = { 100, 500,1000,2000,3000 , 6000 };
	Matrix tabA[6] = { Matrix(n[0],n[0]), Matrix(n[1], n[1]), Matrix(n[2],n[2]) , Matrix(n[3],n[3]) , Matrix(n[4],n[4]),  Matrix(n[5],n[5]) };
	Vector tabb[6] = { Vector(n[0]),Vector(n[1]),Vector(n[2]),Vector(n[3]),Vector(n[4]),Vector(n[5]) };
	Vector tabx[6] = { Vector(n[0]),Vector(n[1]),Vector(n[2]),Vector(n[3]),Vector(n[4]),Vector(n[5]) };
	for (int i = 0; i < 6; i++)
	{
		tabA[i].fillMatrixA(a1A, a2, a3);
		tabb[i].fillVectorB(0);
		start = clock();
		Jacobi(&tabA[i], &tabb[i], &tabx[i], n[i]);
		stop = clock();
		double time = (stop - start) / (double)CLOCKS_PER_SEC;
		cout << "Metoda Jacobiego dla N = " << n[i] << " czas trwania: " << time << "s" << endl;
		tabx[i].fillWithZeros();
		start = clock();
		GaussSeidel(&tabA[i], &tabb[i], &tabx[i], n[i]);
		stop = clock();
		time = (stop - start) / (double)CLOCKS_PER_SEC;
		cout << "Metoda Gaussa-Seidla dla N = " << n[i] << " czas trwania: " << time << "s" << endl;
		tabx[i].fillWithZeros();
		start = clock();
		LU(&tabA[i], &tabb[i], &tabx[i], n[i]);
		stop = clock();
		time = (stop - start) / (double)CLOCKS_PER_SEC;
		cout << "Metoda faktoryzacji LU dla N = " << n[i] << " czas trwania: " << time << "s" << endl;
	}

	return 0;
}
int Jacobi(Matrix* A, Vector* b, Vector* x, int n)
{

	int counter = 0;
	Vector* next = new Vector(n);
	Vector* residuum = new Vector(n);
	while (true) {
		double sum = 0;
		for (int i = 0; i < n; i++)
		{
			double sum = 0;
			for (int j = 0; j < n; j++)
			{
				if (j != i) {
					sum += A->value[i][j] * x->value[j];
				}
			}
			next->value[i] = b->value[i] - sum;
			next->value[i] /= A->value[i][i];
		}
		counter++;
		*x = *next;
		*residuum = ((*A) * (*x) - *b);
		double  norm = residuum->normVect();
		if (norm <= EPSILON)
		{
			break;
		}
		if (isnan(norm)) {
			counter = -1;
			break;
		}
	}

	return counter;

}
int GaussSeidel(Matrix* A, Vector* b, Vector* x, int n)
{
	int counter = 0;
	Vector* residuum = new Vector(n);
	while (true) {
		double sum = 0;
		for (int i = 0; i < n; i++)
		{
			double sum = 0;
			for (int j = 0; j < n; j++)
			{
				if (j != i) {
					sum += A->value[i][j] * x->value[j];
				}

			}
			x->value[i] = b->value[i] - sum;
			x->value[i] /= A->value[i][i];
		}
		counter++;
		*residuum = ((*A) * (*x) - *b);
		double  norm = residuum->normVect();
		if (norm <= EPSILON)
		{
			break;
		}
		if (isnan(norm)) {
			counter = -1;
			break;
		}

	}

	return counter;
}
double LU(Matrix* A, Vector* b, Vector* x, int n)
{

	Matrix L(n, n); //macierz jednostkowa
	Matrix U(n, n);
	for (int i = 0; i < n; i++)
		L.value[i][i] = 1.0;


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			U.value[i][j] = A->value[i][j];
		}
	}
	for (int k = 0; k < n - 1; k++) {
		for (int j = k + 1; j < n; j++)
		{
			L.value[j][k] = U.value[j][k] / U.value[k][k];
			for (int i = k; i < n; i++)
			{
				U.value[j][i] -= L.value[j][k] * U.value[k][i];
			}
		}

	}

	//podstawianie w przod
	Vector y(n);

	for (int i = 0; i < n; i++)
	{
		double sum = 0;
		for (int k = 0; k < i; k++)
		{
			sum += L.value[i][k] * y.value[k];
		}
		y.value[i] = (b->value[i] - sum) / L.value[i][i];

	}
	//podstawienie wstecz
	for (int i = n - 1; i >= 0; i--)
	{
		double sum = 0;
		for (int k = i + 1; k < n; k++)
		{
			sum += U.value[i][k] * x->value[k];
		}
		x->value[i] = (y.value[i] - sum) / U.value[i][i];
	}
	Vector* residuum = new Vector(n);
	*residuum = ((*A) * (*x) - *b);
	return residuum->normVect();


}