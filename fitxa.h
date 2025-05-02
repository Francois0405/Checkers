#pragma once

/**
* FITXER fitxa.h
* AUTOR Jennifer Martinez | Francois Liraud 
* DATA 10/04/2025
* VERSIO 1.0
* Aquest fitxer conte les funcions de la classe Fitxa.h
*/

#ifndef FITXA_H
#define FITXA_H

#include "posicio.hpp"
#include "moviment.h"
const int MAX_MOVIMENTS = 20;

/*
* TIPUS FITXA
* Tipus de fitxa que pot ser normal, dama o empty.
*/

typedef enum {
    TIPUS_NORMAL,
    TIPUS_DAMA,
    TIPUS_EMPTY
} TipusFitxa;

/*
* COLOR FITXA
* Color de la fitxa que pot ser blanc o negre.
*/

typedef enum {
    COLOR_NEGRE,
    COLOR_BLANC
} ColorFitxa;

/*
* CLASS fitxa
* Classe que representa una fitxa del tauler de dames.
* 
* Els seus atributs son:
* - tipus: tipus de la fitxa (normal, dama o empty).
* - color: color de la fitxa (blanc o negre).
* - posicio: posicio de la fitxa al tauler.
* - movimentsValids: array de moviments valids de la fitxa.
* - numMovimentsValids: nombre de moviments valids de la fitxa.
* 
* Els seus metodes son:
* - un constructor per defecte (inicialitza la fitxa a empty).
* - un constructor per parametres (inicialitza la fitxa amb el tipus, color i posicio especificats).
* - getters per obtenir el tipus, color, posicio i moviments valids de la fitxa.
* - setters per establir el tipus, color i posicio de la fitxa.
* - un metode per afegir un moviment valid a la fitxa.
* - un metode per convertir la fitxa en dama.
*/

class Fitxa
{
public:
    Fitxa();
    Fitxa(TipusFitxa tipus, ColorFitxa color, const Posicio& posicio);

    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;
    Posicio getPosicio() const;
    char getLletra() const;
    int getNumMovimentsValids() const;
    const Moviment& getMovimentValid(int index) const;

    void setTipus(TipusFitxa tipus);
    void setColor(ColorFitxa color);
    void setPosicio(const Posicio& posicio);

    void afegeixMovimentValid(const Moviment& moviment);
    void convertirADama();
    void resetMovimentsValids();

private:
    TipusFitxa m_tipus;
    ColorFitxa m_color;
    Posicio m_posicio;

    Moviment m_movimentsValids[MAX_MOVIMENTS];
    int m_numMovimentsValids;
};

#endif