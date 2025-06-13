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

Posicio::Posicio() : m_fila(0), m_columna('a') {}

/**
* Posicio(const string& posicio)
* Constructor que inicialitza la posicio a partir d'una posicio en forma de string.
*/

Posicio::Posicio(const string& posicio)
{
	m_columna = posicio[0];  // 'a' a 'h'
	m_fila = posicio[1] - '0'; // 1 a 8

	// Validació (opcional)
	if (m_fila < 1 || m_fila > 8) m_fila = 1;
	if (m_columna < 'a' || m_columna > 'h') m_columna = 'a';
}

/**
* Posicio(int fila, int columna)
* Constructor que inicialitza la posicio a partir d'una fila i columna.
*/

Posicio::Posicio(int fila, int columna)
{
	m_fila = fila;
	m_columna = 'a' + columna;
}

/**
* getFila
* Getter que retorna la fila de la posicio.
* 
* @return int: fila de la posicio.
*/

int Posicio::getFila() const
{
	return m_fila;
}

/**
* getColumna
* Getter que retorna la columna de la posicio.
* 
* @return int: columna de la posicio.
*/

int Posicio::getColumna() const
{
	return m_columna - 'a';
}

/**
* setFila
* Setter que estableix la fila de la posicio.
* 
* @param fila: fila de la posicio.
* @return void
*/

void Posicio::setFila(int fila)
{
	m_fila = fila;
}

/**
* setColumna
* Setter que estableix la columna de la posicio.
* 
* @param columna: columna de la posicio.
* @return void
*/

void Posicio::setColumna(int columna)
{
	m_columna = 'a' + columna;
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
* stringToPosicio
* Funcio que converteix una posicio en forma de string a una fila i columna.
* 
* @param posicio: string que representa la posicio.
* @param fila: referencia a la fila on es guardara el resultat.
* @param columna: referencia a la columna on es guardara el resultat.
* @return void
*/

void Posicio::stringToPosicio(const string& posicio, int& fila, int& columna)
{
	columna = posicio[0] - 'a'; // Resta en codigo ASCII
	fila = (N_FILES - 1) - (posicio[1] - '0'); // Convertimos a int restandole el caracter 0.
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

istream& operator>>(istream& in, Posicio& pos)
{
	string posStr;
	in >> posStr;  
	pos = Posicio(posStr); 
	return in;
}