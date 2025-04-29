#include "moviment.h"

/**
* FITXER moviment.cpp
* AUTOR Jennifer Martínez | François Liraud
* DATA 29/03/2025
* VERSIO 1.0
* Aquest fitxer conté les funcions de la classe Moviment
*/

Moviment::Moviment() : m_numPosicions(0), m_esCaptura(false), m_numCaptures(0) {}

Moviment::Moviment(const Posicio& posInicial) : m_numPosicions(1), m_esCaptura(false), m_numCaptures(0)
{
	m_posicions[0] = posInicial;
}

int Moviment::getNumPosicions() const //retorn del nujm de posicions que hi ha en el moviment
{
	return m_numPosicions;
}

const Posicio& Moviment::getPosicio(int index) const
{
	return m_posicions[index];
}

Posicio Moviment::getPosicioInicial() const
{
	return m_posicions[0];
}

Posicio Moviment::getPosicioFinal() const
{
	return m_posicions[m_numPosicions - 1];
}

bool Moviment::esMovimentDeCaptura() const //indica si en el moviment s'ha menjat alguna fitxa del rival
{
	return m_esCaptura;
}

int Moviment::getNumCaptures() const
{
	return m_numCaptures;
}

void Moviment::afegeixPosicio(const Posicio& posicio)
{
	if (m_numPosicions < MAX_POSICIONS)
	{
		m_posicions[m_numPosicions++] = posicio;
	}
}

void Moviment::estableixPosicions(const Posicio posicions[], int numPosicions)
{
	m_numPosicions = numPosicions;
	for (int i = 0; i < numPosicions; ++i)
	{
		m_posicions[i] = posicions[i];
	}
}

bool Moviment::contePosicio(const Posicio& posicio) const
{
	for (int i = 0; i < m_numPosicions; ++i)
	{
		if (m_posicions[i] == posicio)
		{
			return true;
		}
	}
	return false;
}