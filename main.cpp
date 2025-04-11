#include "fitxa.h"
#include <iostream>
#include <fstream>

/**
* FITXER main.cpp
* AUTOR Jennifer Martínez | François Liraud
* DATA 19/03/2025
* VERSIO 1.2
* Aquest fitxer conté el main i algunes funcions auxiliars.
*/

using namespace std;

int const N_FILES = 8;
int const N_COLUMNES = 8;

void stringToPosicio(const string& posicio, int& fila, int& columna)
{
	columna = posicio[0] - 'a'; // Resta en codigo ASCII
	fila = (N_FILES - 1) - (posicio[1] - '0'); // Convertimos a int restandole el caracter 0.
}

void llegeixFitxa(const string& nomFitxer, char& tipusFitxa, int& fila, int& columna)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);


	string posicio;
	cin >> tipusFitxa >> posicio;
	stringToPosicio(posicio, fila, columna);
	fitxer.close();

}

void posicioToString(int fila, int columna, string& posicio)
{
	posicio = "aa";
	posicio[0] = ('a' + columna);
	posicio[1] = ('0' + (N_FILES - fila));
}

void escriuFitxa(const string& nomFitxer, char tipusFitxa, int fila, int columna)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);
	

	string posicio;
	posicioToString(fila, columna, posicio);
	fitxer << tipusFitxa << " " << posicio << endl;
	fitxer.close();
}

int main()
{
	cout << "Good luck!" << endl;
}