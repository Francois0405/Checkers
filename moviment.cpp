#include "moviment.h"
#include <iostream>

/**
* FITXER moviment.cpp
* AUTOR Jennifer Martínez | François Liraud
* DATA 29/03/2025
* VERSIO 1.0
* Aquest fitxer conté les funcions de la classe Moviment
*/

/*
* Moviment()
* Constructor per defecte, inicialitza el moviment a 0 posicions i captura a false.
*/

Moviment::Moviment() : m_numPosicions(0), m_esCaptura(false), m_numCaptures(0) {}

/*
* Moviment(const Posicio& posInicial)
* Constructor amb parametre, la posicio inicial
*/

Moviment::Moviment(const Posicio& posInicial) : m_numPosicions(1), m_esCaptura(false), m_numCaptures(0)
{
	m_posicions[0] = posInicial;
}

/*
* getNumPosicions
* Getter que retorna el numero de posicions del moviment.
* 
* @return int: numero de posicions del moviment.
*/

int Moviment::getNumPosicions() const //retorn del nujm de posicions que hi ha en el moviment
{
	return m_numPosicions;
}

/*
* getPosicio
* Getter que retorna la posicio especificada per index.
* 
* @param index: index de la posicio a obtenir.
* @return Posicio: posicio especificada.
*/

const Posicio& Moviment::getPosicio(int index) const
{
	return m_posicions[index];
}

/*
* getPosicioInicial
* Getter que retorna la posicio inicial del moviment.
* 
* @return Posicio: posicio inicial del moviment.
*/

Posicio Moviment::getPosicioInicial() const
{
	return m_posicions[0];
}

/*
* getPosicioFinal
* Getter que retorna la posicio final del moviment.
* 
* @return Posicio: posicio final del moviment.
*/

Posicio Moviment::getPosicioFinal() const
{
	return m_posicions[m_numPosicions - 1];
}

/*
* esMovimentDeCaptura
* Getter que retorna si el moviment es de captura.
* 
* @return bool: true si el moviment es de captura, false en cas contrari.
*/

bool Moviment::esMovimentDeCaptura() const //indica si en el moviment s'ha menjat alguna fitxa del rival
{
	return m_esCaptura;
}

/*
* getNumCaptures
* Getter que retorna el numero de captures del moviment.
* 
* @return int: numero de captures del moviment.
*/

int Moviment::getNumCaptures() const
{
	return m_numCaptures;
}

/*
* afegeixPosicio
* Metode que afegeix una posicio al moviment si hi ha espai disponible.
* 
* @param posicio: posicio a afegir.
* @return void
*/

void Moviment::afegeixPosicio(const Posicio& posicio)
{
	if (m_numPosicions < MAX_POSICIONS)
	{
		m_posicions[m_numPosicions++] = posicio;
	}
}

/*
* estableixPosicions
* Metode que estableix les posicions del moviment.
* 
* @param posicions: array de posicions a establir.
* @param numPosicions: numero de posicions a establir.
* @return void
*/

void Moviment::estableixPosicions(const Posicio posicions[], int numPosicions)
{
	m_numPosicions = numPosicions;
	for (int i = 0; i < numPosicions; i++)
	{
		m_posicions[i] = posicions[i];
	}
}

/*
* contePosicio
* Metode que comprova si una posicio es troba dins del moviment.
* 
* @param posicio: posicio a comprovar.
* @return bool: true si la posicio es troba dins del moviment, false en cas contrari.
*/

bool Moviment::contePosicio(const Posicio& posicio) const
{
	int i = 0;
	bool conte = false;
	while (i < m_numPosicions && !conte) //busquem la posicio en el moviment
	{
		if (m_posicions[i] == posicio) //si la trobem retornem true
		{
			conte = true;
		}
		else
		{
			i++;
		}
	}

	return conte;
}