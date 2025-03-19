#pragma once
#include "posicio.h"
#include <iostream>

#ifndef TAULER_H
#define TAULER_H

/**
* FITXER tauler.h
* AUTOR François Liraud
* DATA 19/03/2025
* VERSIO 1.0
* Aquest fitxer conté la classe Tauler
*/

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
};

#endif