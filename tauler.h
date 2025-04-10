#pragma once
/**
* FITXER tauler.h
* AUTOR Jennifer Martínez
* DATA 10/04/2025
* VERSIO 1.0
* Aquest fitxer conté les funcions de la classe Tauler.h
*/


#include "posicio.h"
#include <iostream>
#include "Fitxa.h"
#include <string>

#ifndef TAULER_H
#define TAULER_H

const int N_FILES = 8;
const int N_COLUMNES = 8;
using namespace std;

class Tauler
{
public:
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();
	void getPosicionsPossibles(const Posicio& origen,
	int& nPosicions, Posicio posicionsPossibles[]);
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	string toString() const;
private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
};

#endif