#include "fitxa.h"
#include "posicio.hpp"
#include "tauler.hpp"
#include "moviment.h"

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

//void llegeixFitxa(const string& nomFitxer, char& tipusFitxa, int& fila, int& columna)
//{
//	ifstream fitxer;
//	fitxer.open(nomFitxer);
//
//
//	string posicio;
//	cin >> tipusFitxa >> posicio;
//	stringToPosicio(posicio, fila, columna);
//	fitxer.close();
//
//} // quitar open todo el rato, pasar por parametro ifstream
//
//
//
//void escriuFitxa(const string& nomFitxer, char tipusFitxa, int fila, int columna)
//{
//	ofstream fitxer;
//	fitxer.open(nomFitxer);
//	
//
//	string posicio;
//	posicioToString(fila, columna, posicio);
//	fitxer << tipusFitxa << " " << posicio << endl;
//	fitxer.close();
//}

int main()
{
	cout << "Here we go!" << endl;
	Tauler taulerDames;
	string taulerString;
	taulerDames.inicialitza("taulerInicial.txt");
	taulerString = taulerDames.toString();
	cout << taulerString;
}