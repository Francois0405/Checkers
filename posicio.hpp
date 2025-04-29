#pragma once
#ifndef POSICIO_HPP
#define POSICIO_HPP
/**
* FITXER posicio.h
* AUTOR Jennifer Martínez | François Liraud
* DATA 10/04/2025
* VERSIO 1.0
* Aquest fitxer conté les funcions de la classe Posicio.h
*/


#include <string>

using namespace std;

/*
* CLASS Posicio
* Classe que representa una posicio al tauler de dames.
* 
* Els seus atributs son:
* - fila: fila de la posicio (1 a 8).
* - columna: columna de la posicio (a - h).
* 
* Els seus metodes son:
* - un constructor per defecte (inicialitza la posicio a (0, 'a')).
* - un constructor per parametres (inicialitza la posicio amb la fila i columna especificades).
* - un constructor que inicialitza la posicio a partir d'una posicio en forma de string.
* - getters per obtenir la fila i columna de la posicio.
* - setters per establir la fila i columna de la posicio.
* - un operador == per saber si dues posicions son iguals.
* - un operador != per saber si dues posicions son diferents.
* - un metode per convertir una posicio en forma de string a una fila i columna.
* - un metode per convertir una fila i columna en forma de string a una posicio.
*/

class Posicio 
{
public:
    Posicio();
    Posicio(const string& posicio);
    Posicio(int fila, int columna);

    int getFila() const;
    int getColumna() const;

    void setFila(int fila);
    void setColumna(int columna);

    bool operator==(const Posicio& posicio) const;
    bool operator!=(const Posicio& posicio) const;

    void stringToPosicio(const string& posicio, int& fila, int& columna);
    void posicioToString(string& posicio) const;

private:
    int m_fila;    
    char m_columna; 
};

ostream& operator<<(ostream& out, const Posicio& pos);

#endif