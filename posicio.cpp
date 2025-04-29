#include "posicio.h"

/**
* FITXER posicio.cpp
* AUTOR Jennifer Martínez | François Liraud
* DATA 29/03/2025
* VERSIO 1.0
* Aquest fitxer conté les funcions de la classe Posicio
*/

const int N_FILES = 8;
const int N_COLUMNES = 8;

Posicio::Posicio() : m_fila(0), m_columna('a') {}

Posicio::Posicio(const string& posicio)
{
	m_columna = posicio[0];
	m_fila = posicio[1] - '0';
}

Posicio::Posicio(int fila, int columna)
{
	m_fila = fila;
	m_columna = 'a' + columna;
}

int Posicio::getFila() const
{
	return m_fila;
}

int Posicio::getColumna() const
{
	return m_columna - 'a';
}

void Posicio::setFila(int fila)
{
	m_fila = fila;
}

void Posicio::setColumna(int columna)
{
	m_columna = 'a' + columna;
}

bool Posicio::operator==(const Posicio& posicio) const
{
	return (m_fila == posicio.m_fila && m_columna == posicio.m_columna);
}

bool Posicio::operator!=(const Posicio& posicio) const
{

}

void Posicio::stringToPosicio(const string& posicio, int& fila, int& columna)
{
	columna = posicio[0] - 'a'; // Resta en codigo ASCII
	fila = (N_FILES - 1) - (posicio[1] - '0'); // Convertimos a int restandole el caracter 0.
}

void Posicio::posicioToString(string& posicio) const
{
	posicio = "aa";
	posicio[0] = ('a' + m_columna);
	posicio[1] = ('0' + (N_FILES - m_fila));
}