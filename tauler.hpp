#pragma once
/**
* FITXER tauler.h
* AUTOR Jennifer Martinez | Francois Liraud
* DATA 10/04/2025
* VERSIO 1.0
* Aquest fitxer conte les funcions de la classe Tauler.h
*/

#include "posicio.hpp"
#include "fitxa.h"
#include <iostream>
#include <string>
#include <vector>

#ifndef TAULER_HPP
#define TAULER_HPP

const int N_FILES = 8;
const int N_COLUMNES = 8;
using namespace std;

/*
* CLASS Tauler
* Classe que gestiona el tauler de dames, es la entitat mes gran del projecte.
*  
* Els seu atribut es una matriu (tauler) de caselles tipus Fitxa ja que aquestes poden ser
* d'un color, d'un altre o "EMPTY".
* 
* Els seus metodes son: 
* un constructor per defecte (inicialitza tot a empty).
* una funcio que inicialitza el tauler amb les dades d'un fitxer.
* una funcio que actualitza els moviments valids de totes les peces del joc i les guarda
*	en un array de moviments valids de tipus moviment a l'objecte fitxa.
* un getter per retornar aquest array de moviments valids d'una fitxa.
* una funcio per moure una peca, primerament comprova si el desti es un moviment valid,
*	si no ho aconsegueix retorna false, y fa l'accio de matar peces contraries en el moviment.
* una funcio per generar un string amb l’estat actual del tauler de joc
*/

class Tauler
{
public:
	Tauler();
	void inicialitza(const string& nomFitxer);

	void actualitzaMovimentsValids();
	void getPosicionsPossibles(const Posicio& origen, vector<Posicio>& posicionsPossibles);
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	string toString() const;


private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
	// Auxiliars
	bool esDinsTauler(int fila, int col) const;
	void getCapturesDama(const Fitxa& fitxa, const Moviment& movActual, vector<Moviment>& pendents);
	void calculaMovimentsFitxa(int fila, int col);
	void getCapturesDisponibles(const Fitxa& fitxa, const Moviment& movActual,
		vector<Moviment>& pendents);

};

#endif