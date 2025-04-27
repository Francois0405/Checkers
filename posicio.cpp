#include "posicio.h"

/**
* FITXER posicio.cpp
* AUTOR Jennifer Martínez | François Liraud
* DATA 19/03/2025
* VERSIO 1.0
* Aquest fitxer conté les funcions de la classe Posicio
*/

const int N_FILES = 8;
const int N_COLUMNES = 8;

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