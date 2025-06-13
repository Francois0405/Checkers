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
* Posicio(const string& posicio)
* Constructor que inicialitza la posicio a partir d'una posicio en forma de string.
*/

Posicio::Posicio(const string& posicio)
{
	m_columna = posicio[0] - 'a';  // 'a' a 'h'
	m_fila = 8 - (posicio[1] - '0'); // Invertim la logica a1 = [0][7]
}

/**
* Posicio(int fila, int columna)
* Constructor que inicialitza la posicio a partir d'una fila i columna.
*/

Posicio::Posicio(int fila, int columna) : m_fila(fila), m_columna(columna) {}

/**
* operator==
* Operador que compara si dues posicions son iguals.
* 
* @param posicio: posicio a comparar.
* @return bool: true si les posicions son iguals, false en cas contrari.
*/

bool Posicio::operator==(const Posicio& posicio) const
{
	bool igual = false;
	if (m_fila == posicio.m_fila && m_columna == posicio.m_columna)
	{
		igual = true;
	}
	return igual;
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
	bool diferent = false;
	if (m_fila != posicio.m_fila || m_columna != posicio.m_columna)
	{
		diferent = true;
	}
	return diferent;
}


/**
* posicioToString
* Funcio que converteix una posicio a una string.
* 
* @param posicio: referencia a la string on es guardara el resultat.
* @return void
*/

void Posicio::posicioToString(string& posicio) const
{
	posicio = "";
	posicio += m_columna;
	posicio += to_string(m_fila);
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
	string posicio;
	pos.posicioToString(posicio);
	out << posicio;
	return out;
}