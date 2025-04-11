#pragma once

/**
* FITXER fitxa.h
* AUTOR Jennifer Martínez | François Liraud 
* DATA 10/04/2025
* VERSIO 1.0
* Aquest fitxer conté les funcions de la classe Fitxa.h
*/

#ifndef FITXA_H
#define FITXA_H
#include "Posicio.h"
#include "Moviment.h"
const int MAX_MOVIMENTS = 20;

typedef enum {
    TIPUS_NORMAL,
    TIPUS_DAMA,
    TIPUS_EMPTY
} TipusFitxa;

typedef enum {
    COLOR_NEGRE,
    COLOR_BLANC
} ColorFitxa;

class Fitxa
{
public:
    Fitxa();
    Fitxa(TipusFitxa tipus, ColorFitxa color, const Posicio& posicio);

    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;
    Posicio getPosicio() const;
    int getNumMovimentsValids() const;
    const Moviment& getMovimentValid(int index) const;

    void setTipus(TipusFitxa tipus);
    void setColor(ColorFitxa color);
    void setPosicio(const Posicio& posicio);

    void afegeixMovimentValid(const Moviment& moviment);
    void convertirADama();
private:
    TipusFitxa m_tipus;
    ColorFitxa m_color;
    Posicio m_posicio;

    Moviment m_movimentsValids[MAX_MOVIMENTS];
    int m_numMovimentsValids;
};

#endif