#include "fitxa.h"

/**
* FITXER fitxa.cpp
* AUTOR Jennifer Martínez | François Liraud
* DATA 19/03/2025
* VERSIO 1.0
* Aquest fitxer conté les funcions de la classe Fitxa
*/

Fitxa::Fitxa() : m_tipus(TIPUS_EMPTY), m_color(COLOR_BLANC) {}

Fitxa::Fitxa(TipusFitxa tipus, ColorFitxa color, const Posicio& posicio) : m_tipus(tipus), m_color(color), m_posicio(posicio) {}

TipusFitxa Fitxa::getTipus() const
{
	return m_tipus;
}

ColorFitxa Fitxa::getColor() const
{
	return m_color;
}

Posicio Fitxa::getPosicio() const
{
	return m_posicio;
}

int Fitxa::getNumMovimentsValids() const
{
	return m_numMovimentsValids;
}
const Moviment& Fitxa::getMovimentValid(int index) const
{
	return m_movimentsValids[index];
}

void Fitxa::setTipus(TipusFitxa tipus)
{
	m_tipus = tipus;
}
void Fitxa::setColor(ColorFitxa color)
{
	m_color = color;
}

void Fitxa::setPosicio(const Posicio& posicio)
{
	m_posicio = posicio;
}

void Fitxa::afegeixMovimentValid(const Moviment& moviment)
{
	if (m_numMovimentsValids < MAX_MOVIMENTS)
	{
		m_movimentsValids[m_numMovimentsValids++] = moviment;
	}
}
void Fitxa::convertirADama()
{
	if (m_tipus == TIPUS_NORMAL)
		m_tipus = TIPUS_DAMA;
}