#include "iostream"
#include "cmath"
#include "fstream"
#include "cstdlib"

using namespace std;

const int    MAXEQ = 100;

bool dominacja(int num, double A[][MAXEQ + 1])
{
	double spr = 0;
	for (int i = 0; i < num; i++)
	{
		spr = abs(A[i][i]);
		for (int j = 0; j < num; j++)
		{
			if (A[i][j] != A[i][i])
			{
				spr -= abs(A[i][j]);
			}
		}
		if (spr <= 0)
		{
			return false;
		}
	}
	return true;
}


int main()
{
	double A[MAXEQ][MAXEQ + 1];
	float M[MAXEQ][MAXEQ];
	float N[MAXEQ];
	float b[MAXEQ];
	float x1[MAXEQ];
	float x2[MAXEQ];

	int num, iter;
	int i, j;

	ifstream fin; //zmienne do plików txt
	// Odczyt z pliku

	fin.open("C:\\Users\\micha\\source\\repos\\Jacobs\\in.txt");
	fin >> num; //wielkość macierzy

	for (i = 0; i < num; i++)
	{
		for (j = 0; j <= num; j++)
		{
			fin >> A[i][j];
		}
	}
	fin.close();

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num + 1; j++)
		{
			cout << A[i][j] << "	";
		}
		cout << endl;
	}

	cout << endl << "---------------------------------------------------------" << endl << endl;

	if (dominacja(num, A))
	{
		cout << "Macierz jest diagonalnie dominujaca!" << endl;
	}
	else
	{
		cout << "Macierz jest diagonalnie slabo dominujaca!" << endl;
	}

	cout << endl << "---------------------------------------------------------" << endl << endl;


	// b
	for (int i = 0; i < num; i++)
	{
		b[i] = A[i][num];
		//cout << "x" << i + 1 << " = " << b[i] << endl;
	}

	// N = D^-1

	cout << "Macierz odwrotna: " << endl;

	for (i = 0; i < num; i++)
		N[i] = 1 / A[i][i];

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			if (A[i][j] != A[i][i])
			{
				cout << 0 << "	";
			}
			else
			{
				cout << N[i] << "	";
			}
		}
		cout << endl;
	}

	cout << endl << "---------------------------------------------------------" << endl << endl;
	cout << "Macierz L + U: " << endl;

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			if (A[i][j] != A[i][i])
			{
				cout << A[i][j] << "	";
			}
			else
			{
				cout << 0 << "	";
			}
		}
		cout << endl;
	}

	cout << endl << "---------------------------------------------------------" << endl << endl;

	// M = -D^-1 (L + U)
	for (i = 0; i < num; i++)
		for (j = 0; j < num; j++)
			if (i == j)
				M[i][j] = 0;
			else
				M[i][j] = -(A[i][j] * N[i]);

	//Wyliczenie X
	for (i = 0; i < num; i++)
		x1[i] = 0;

	cout << "Ile iteracji algorytmu wykonac?" << endl;
	cin >> iter;

	for (int k = 0; k < iter; k++) {
		for (i = 0; i < num; i++) {
			x2[i] = N[i] * b[i];
			for (j = 0; j < num; j++)
				x2[i] += M[i][j] * x1[j];
		}
		for (i = 0; i < num; i++)
			x1[i] = x2[i];
	}

	cout << "Wyniki dla " << iter << " iteracj:" << endl;
	for (i = 0; i < num; i++)
		cout << "x[" << i + 1 << "] = " << x1[i] << endl;

	return 0;

}