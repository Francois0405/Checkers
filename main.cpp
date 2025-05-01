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
	cout << "    ___             ______      ______                          " << endl
		<< "   |_  |            |  _  \\     |  _  \\                         " << endl
		<< "     | | ___   ___  | | | |___  | | | |__ _ _ __ ___   ___  ___ " << endl
		<< "     | |/ _ \\ / __| | | | / _ \\ | | | / _` | '_ ` _ \\ / _ \\/ __|" << endl
		<< "/ \\__/ / (_) | (__  | |/ /  __/ | |/ / (_| | | | | | |  __/\\__ \\ " << endl
		<< " \\____/ \\___/ \\___| |___/ \\___| |___/ \\__,_|_| |_| |_|\\___||___/" << endl << endl;

	cout << endl << "==============================================================" << endl << endl;
	cout << "1. Jugar contra un adversari" << endl
		<< "2. Jugar contra un ordinador" << endl
		<< "3. Configuracio" << endl
		<< "4. Depuracio" << endl
		<< "5. Sortir" << endl;
	cout << endl << "Trieu una opcio: ";
	int opcio;
	cin >> opcio;
	while (opcio > 5 || opcio < 1)
	{
		cout << "ERROR: Trieu una opcio valida: ";
		cin >> opcio;
	}
	return opcio;
}

void config(Tauler& taulerDames)
{
	int opcio2;
	string nomFitxer;
	char confirmacio;
	string taulerString;
	cout << "Configuracio" << endl << endl;
	cout << "1. Canviar la plantilla del tauler inicial" << endl;
	cout << endl << "Trieu una opcio: ";
	cin >> opcio2;
	switch (opcio2)
	{
	case 1:
		do {
			cout << "Introdueix el nom de fitxer a partir del qual vols iniciar la partida" << endl;
			cin >> nomFitxer;
			taulerDames.inicialitza(nomFitxer);
			system("CLS");
			cout << "Es aquest el tauler que vols inicialitzar? (*/N)" << endl;
			taulerString = taulerDames.toString();
			cout << endl << taulerString << endl;
			cout << "* Atencio, si poseu un nom d'un arxiu invalid, el tauler s'inicialitzara a \"buit\"" << endl;
			cin >> confirmacio;
			system("CLS");
		} while (confirmacio == 'N' || confirmacio == 'n');
		cout << "Configurat!" << endl;
		break;
	default:
		cout << "Opcio no valida" << endl;
		break;
	}
}

int main()
{
	int opcio = 0;
	char confirmacio;
	Tauler taulerDames;
	taulerDames.inicialitza("taulerInicial.txt");
	string taulerString;
	string nomFitxer;
	Posicio origen("c3");
	Posicio final("d4");
	while (opcio != 5)
	{
		opcio = menu();
		system("CLS");

		switch (opcio)
		{
		case 1:
			cout << "Jugant contra huma" << endl;


			taulerDames.mouFitxa(origen, final);
			taulerString = taulerDames.toString();
			cout << taulerString;
			break;
		case 2:
			cout << "Jugant contra maquina" << endl;
			break;
		case 3:
			config(taulerDames);
			break;
		case 4:
			cout << "Menu de depuracio" << endl;
			cout << "Introdueix el nom de fitxer a mostrar" << endl;
			cin >> nomFitxer;
			taulerDames.inicialitza(nomFitxer);
			taulerString = taulerDames.toString();
			cout << taulerString;
			break;
		case 5:
			cout << "Sortint..." << endl;
			break;
		default: // Errors
 			cout << "Error: seleccio no valida" << endl;
			break;
		}
	}
	return 0;
}