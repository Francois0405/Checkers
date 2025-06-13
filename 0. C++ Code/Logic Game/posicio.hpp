#pragma once
#ifndef POSICIO_HPP
#define POSICIO_HPP

#include <string>
using namespace std;

class Posicio
{
public:
    Posicio(); // Inicializa a (0,0)
    Posicio(const string& posicio); // Desde notación "a1"
    Posicio(int fila, int columna); // Desde índices (0-7, 0-7)

    // Getters
    int getFila() const;    // Devuelve 0-7
    int getColumna() const; // Devuelve 0-7

    // Para notación de tablero
    char getColumnaChar() const; // Devuelve 'a'-'h'
    int getFilaNotacio() const;  // Devuelve 1-8

    // Setters
    void setFila(int fila);
    void setColumna(int columna);

    // Operadores   
    bool operator==(const Posicio& posicio) const;
    bool operator!=(const Posicio& posicio) const;

    // Conversión
    string toString() const;

private:
    int m_fila;    // 0-7 (0 = primera fila)
    int m_columna; // 0-7 (0 = columna 'a')
};

ostream& operator<<(ostream& out, const Posicio& pos);

#endif