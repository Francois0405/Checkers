#include "moviment.h"
#include <iostream>

/**
* FITXER moviment.cpp
* AUTOR Jennifer Martinez | Francois Liraud
* DATA 29/03/2025
* VERSIO 1.0
* Aquest fitxer conte les funcions de la classe Moviment
*/

/*
* Moviment()
* Constructor per defecte, inicialitza el moviment a 0 posicions i captura a false.
*/

Moviment::Moviment() : m_numPosicions(0), m_esCaptura(false) {}

/*
* Moviment(const Posicio& posInicial)
* Constructor amb parametre, la posicio inicial
*/

Moviment::Moviment(const Posicio& posInicial) : m_esCaptura(false), m_numCaptures(0)
{
	m_posicions.push_back(posInicial);
}

Moviment::Moviment(const Posicio& posInicial, const Posicio& posFinal)
{
	m_numPosicions = 2;
	m_posicions.push_back(posInicial);
	m_posicions.push_back(posFinal);
}

/*
* getNumPosicions
* Getter que retorna el numero de posicions del moviment.
* 
* @return int: numero de posicions del moviment.
*/

int Moviment::getNumPosicions() const //retorn del num de posicions que hi ha en el moviment
{
	return m_posicions.size();
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
	return m_posicions.front();
}

/*
* getPosicioFinal
* Getter que retorna la posicio final del moviment.
* 
* @return Posicio: posicio final del moviment.
*/

Posicio Moviment::getPosicioFinal() const
{
	return m_posicions.back();
}

/*
* esMovimentDeCaptura
* Getter que retorna si el moviment es de captura.
* 
* @return bool: true si el moviment es de captura, false en cas contrari.
*/

bool Moviment::getEsMovimentDeCaptura() const //indica si en el moviment s'ha menjat alguna fitxa del rival
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
* setEsMovimentDeCaptura
* Setter que estableix si el moviment es de captura.
* 
* @param esCaptura: true si el moviment es de captura, false en cas contrari.
* @return void
*/

void Moviment::setEsMovimentDeCaptura(bool esCaptura)
{
	m_esCaptura = esCaptura;
	if (esCaptura)
	{
		m_numCaptures = m_posicions.size() - 1;
	}
	else
	{
		m_numCaptures = 0;

	}
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
	m_posicions.push_back(posicio);
}

/*
* estableixPosicions
* Metode que estableix les posicions del moviment.
* 
* @param posicions: array de posicions a establir.
* @param numPosicions: numero de posicions a establir.
* @return void
*/

void Moviment::estableixPosicions(const vector<Posicio>& posicions)
{
	m_posicions = posicions;
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
	bool conte = false;
	for (int i = 0; i < m_posicions.size(); ++i)
	{
		if (m_posicions[i] == posicio)
		{
			conte = true;
		}
	}
	return conte;
}

ostream& operator<<(ostream& out, const Moviment& mov)
{
	out << "Moviment: ";
	out << mov.getPosicioInicial();
	out << " -> ";
	out << mov.getPosicioFinal();
	if (mov.getEsMovimentDeCaptura())
	{
		out << " (C)" << endl;
	}
	return out;
}

istream& operator>>(istream& in, Moviment& mov) {
	Posicio inicio, fin;
	if (in >> inicio >> fin) {  // Reads two positions
		mov = Moviment(inicio);  // Create move with start position
		mov.afegeixPosicio(fin); // Add end position
	}
	return in;
}