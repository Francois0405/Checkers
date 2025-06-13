#include "posicio.hpp"
#include <iostream>

/**
* FITXER posicio.cpp
* AUTOR Jennifer Martinez | Francois Liraud
* DATA 29/03/2025
* VERSIO 1.0
* Aquest fitxer conte les funcions de la classe Posicio
*/

const int N_FILES = 8;
const int N_COLUMNES = 8;

/**
* Posicio()
* Constructor per defecte, inicialitza la posicio a (0, 'a').
*/

Posicio::Posicio() : m_fila(0), m_columna(0) {}

/**
* Posicio(const string& posicio)
* Constructor que inicialitza la posicio a partir d'una posicio en forma de string.
*/

Posicio::Posicio(const string& posicio)
{
	if (posicio.length() != 2)
		throw invalid_argument("Posicio invalida: " + posicio);

	m_columna = tolower(posicio[0]) - 'a';
	m_fila = 8 - (posicio[1] - '0'); // Convierte a índice 0-7

	if (m_columna < 0 || m_columna > 7 || m_fila < 0 || m_fila > 7)
		throw invalid_argument("Posicio fora del tauler: " + posicio);
}

/**
* Posicio(int fila, int columna)
* Constructor que inicialitza la posicio a partir d'una fila i columna.
*/

Posicio::Posicio(int fila, int columna)
	: m_fila(fila), m_columna(columna)
{
	if (fila < 0 || fila > 7 || columna < 0 || columna > 7)
		throw out_of_range("Indices fora de rang (0-7)");
}

int Posicio::getFila() const { return m_fila; }
int Posicio::getColumna() const { return m_columna; }

char Posicio::getColumnaChar() const { return 'a' + m_columna; }
int Posicio::getFilaNotacio() const { return 8 - m_fila; }


void Posicio::setFila(int fila)
{
	if (fila < 0 || fila > 7)
		throw out_of_range("Fila ha de ser 0-7");
	m_fila = fila;
}

void Posicio::setColumna(int columna)
{
	if (columna < 0 || columna > 7)
		throw out_of_range("Columna ha de ser 0-7");
	m_columna = columna;
}



/**
* operator==
* Operador que compara si dues posicions son iguals.
* 
* @param posicio: posicio a comparar.
* @return bool: true si les posicions son iguals, false en cas contrari.
*/

bool Posicio::operator==(const Posicio& posicio) const
{
	return m_fila == posicio.m_fila && m_columna == posicio.m_columna;
}

/**
* operator!=
* Operador que compara si dues posicions son diferents.
* 
* @param posicio: posicio a comparar.
* @return bool: true si les posicions son diferents, false en cas contrari.
*/

bool Posicio::operator!=(const Posicio& posicio) const
{
	return !(*this == posicio);
}


string Posicio::toString() const
{
	string s;
	s += getColumnaChar();
	s += to_string(getFilaNotacio());
	return s;
}

/**
* operator<<
* Operador que imprimeix la posicio en format string.
* 
* @param out: referencia a l'ostream on es imprimira la posicio.
* @param pos: referencia a la posicio a imprimir.
* @return ostream&: referencia a l'ostream.
*/

ostream& operator<<(ostream& out, const Posicio& pos)
{
	out << pos.toString();
	return out;
}