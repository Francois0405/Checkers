#include "fitxa.h"
#include "posicio.hpp"
#include "tauler.hpp"
#include "moviment.h"

#include <iostream>
#include <fstream>
#include <string>

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

int menu()
{
	cout << "   ___             ______      ______                          " << endl
		<< "   |_  |            |  _  \\     |  _  \\                         " << endl
		<< "     | | ___   ___  | | | |___  | | | |__ _ _ __ ___   ___  ___ " << endl
		<< "     | |/ _ \\ / __| | | | / _ \\ | | | / _` | '_ ` _ \\ / _ \\/ __|" << endl
		<< "/ \\__/ / (_) | (__  | |/ /  __/ | |/ / (_| | | | | | |  __/\\__ \\ " << endl
		<< " \\____/ \\___/ \\___| |___/ \\___| |___/ \\__,_|_| |_| |_|\\___||___/" << endl << endl;

	cout << endl << "==============================================================" << endl << endl;
	cout << "1. Jugar contra un adversari" << endl
		<< "2. Jugar contra un ordinador" << endl
		<< "3. Depuracio" << endl
		<< "4. Sortir" << endl;
	cout << endl << "Trieu una opcio: ";
	int opcio;
	cin >> opcio;
	while (opcio > 4 || opcio < 1)
	{
		cout << "ERROR: Trieu una opcio valida: ";
		cin >> opcio;
	}
	return opcio;
}

int main()
{
	int opcio;
	opcio = menu();
	system("CLS");
	Tauler taulerDames;
	string taulerString;
	string nomFitxer;
	switch (opcio)
	{
	case 1:
		cout << "Jugant contra huma" << endl;
		break;
	case 2:
		cout << "Jugant contra maquina" << endl;
		break;
	case 3:
		cout << "Menu de depuracio" << endl;
		cout << "Introdueix el nom de fitxer a mostrar" << endl;
		cin >> nomFitxer;
		taulerDames.inicialitza(nomFitxer);
		taulerString = taulerDames.toString();
		cout << taulerString;
		break;
	default: // Cas 4 i errors
		cout << "Sortint..." << endl;
		break;
	}
	return 0;
	
	
}