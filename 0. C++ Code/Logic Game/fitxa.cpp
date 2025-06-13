#include "fitxa.h"
#include "GraphicManager.h"
#include "info_joc.hpp"
#include <iostream>
using namespace std;

/**
* FITXER fitxa.cpp
* AUTOR Jennifer Martinez | Francois Liraud
* DATA 19/03/2025
* VERSIO 1.0
* Aquest fitxer conte les funcions de la classe Fitxa
*/

/*
* Fitxa()
* Constructor per defecte, inicialitza la fitxa a empty "de color blanc" (sense color).
*/

Fitxa::Fitxa() : m_tipus(TIPUS_EMPTY), m_color(COLOR_BLANC) {}

/*
* Fitxa(TipusFitxa tipus, ColorFitxa color, const Posicio& posicio)
* Constructor per parametres, inicialitza la fitxa amb el tipus, color i posicio especificats.
*/

Fitxa::Fitxa(TipusFitxa tipus, ColorFitxa color, const Posicio& posicio) : m_tipus(tipus), m_color(color), m_posicio(posicio) {}

/*
* getTipus
* Getter que retorna el tipus de la fitxa.
* 
* @return TipusFitxa: tipus de la fitxa.
*/

TipusFitxa Fitxa::getTipus() const
{
	return m_tipus;
}

/*
* getColor
* Getter que retorna el color de la fitxa.
* 
* @return ColorFitxa: color de la fitxa.
*/

ColorFitxa Fitxa::getColor() const
{
	return m_color;
}

/*
* getPosicio
* Getter que retorna la posicio de la fitxa.
* 
* @return Posicio: posicio de la fitxa.
*/

Posicio Fitxa::getPosicio() const
{
	return m_posicio;
}

/*
* getLletra
* Getter que retorna la lletra traduida

* @return string: Lletra traduida  
*/

char Fitxa::getLletra() const
{
	char lletra = '_';
	
	if (m_color == COLOR_BLANC)
	{
		if (m_tipus == TIPUS_NORMAL)
			lletra = 'O';
		if (m_tipus == TIPUS_DAMA)
			lletra = 'D';
	}
	else if (m_color == COLOR_NEGRE)
	{
		if (m_tipus == TIPUS_NORMAL)
			lletra = 'X';
		if (m_tipus == TIPUS_DAMA)
			lletra = 'R';
	}
	return lletra;
}

/*
* getNumMovimentsValids
* Getter que retorna el numero de moviments valids de la fitxa.
* 
* @return int: numero de moviments valids.
*/

int Fitxa::getNumMovimentsValids() const
{
	return m_movimentsValids.size();
}

/*
* getMovimentValid
* Getter que retorna el moviment valid especificat per index.
* 
* @param index: index del moviment valid.
* @return Moviment: moviment valid especificat.
*/

const Moviment& Fitxa::getMovimentValid(int index) const
{
	return m_movimentsValids[index];
}

/*
* setTipus
* Setter que estableix el tipus de la fitxa.
* 
* @param tipus: tipus de la fitxa.
* @return void
*/

void Fitxa::setTipus(TipusFitxa tipus)
{
	m_tipus = tipus;
}

/*
* setColor
* Setter que estableix el color de la fitxa.
* 
* @param color: color de la fitxa.
* @return void
*/

void Fitxa::setColor(ColorFitxa color)
{
	m_color = color;
}

/*
* setPosicio
* Setter que estableix la posicio de la fitxa.
* 
* @param posicio: posicio de la fitxa.
* @return void
*/
	
void Fitxa::setPosicio(const Posicio& posicio)
{
	m_posicio = posicio;
}

/*
* afegeixMovimentValid
* Metode que afegeix un moviment valid a la fitxa si hi ha espai disponible.
* 
* @param moviment: moviment valid a afegir.
* @return void
*/

void Fitxa::afegeixMovimentValid(const Moviment& moviment)
{
	if (moviment.getEsMovimentDeCaptura())
	{
		Posicio desti = moviment.getPosicioFinal();
		cout << "[DEBUG] Afegit moviment de captura per a fitxa " << getLletra()
			<< " cap a (" << desti.getFila() << ", " << desti.getColumna() << ")" << endl;
	} //QUITAR DPS

	m_movimentsValids.push_back(moviment);
}

/*
* convertirADama
* Metode que converteix la fitxa en dama si es un tipus normal.
* 
* @return void
*/

void Fitxa::convertirADama()
{
	if (m_tipus == TIPUS_NORMAL)
		m_tipus = TIPUS_DAMA;
}

void Fitxa::resetMovimentsValids()
{
	m_movimentsValids.clear();
}


void Fitxa::visualitza() const
{
	if (m_tipus != TIPUS_EMPTY)
	{
		int col = m_posicio.getColumna();
		int fila = m_posicio.getFila();

		int posX = POS_X_TAULER + CASELLA_INICIAL_X + (col * AMPLADA_CASELLA);
		int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + (fila * ALCADA_CASELLA);

		IMAGE_NAME grafic;
		if (m_color == COLOR_BLANC) {
			if (m_tipus == TIPUS_DAMA)
				grafic = GRAFIC_DAMA_BLANCA;
			else
				grafic = GRAFIC_FITXA_BLANCA;
		}
		else {
			if (m_tipus == TIPUS_DAMA)
				grafic = GRAFIC_DAMA_NEGRA;
			else
				grafic = GRAFIC_FITXA_NEGRA;
		}
		GraphicManager::getInstance()->drawSprite(grafic, posX, posY);
	}
}