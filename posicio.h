#pragma once
#ifndef POSICIO_H
#define POSICIO_H
/**
* FITXER posicio.h
* AUTOR Jennifer Martínez
* DATA 10/04/2025
* VERSIO 1.0
* Aquest fitxer conté les funcions de la classe Posicio.h
*/

#include <string>
using namespace std;

class Posicio {
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

    string toString() const;

private:
    int m_fila;    
    char m_columna; 
};


#endif