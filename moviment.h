#pragma once

/**
* FITXER moviment.h
* AUTOR Jennifer Martinez | Francois Liraud
* DATA 10/04/2025
* VERSIO 1.0
* Aquest    fitxer conte les funcions de la classe Moviment.h
*/

#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "posicio.hpp"
const int MAX_POSICIONS = 20;

class Moviment {
public:
    Moviment();
    Moviment(const Posicio& posInicial);

    int getNumPosicions() const;
    const Posicio& getPosicio(int index) const;
    Posicio getPosicioInicial() const;
    Posicio getPosicioFinal() const;
    bool getEsMovimentDeCaptura() const;
    int getNumCaptures() const;

    void setEsMovimentDeCaptura(bool esCaptura);

    void afegeixPosicio(const Posicio& posicio);
    void estableixPosicions(const Posicio posicions[], int numPosicions);
    bool contePosicio(const Posicio& posicio) const;

private:
    Posicio m_posicions[MAX_POSICIONS];
    int m_numPosicions;
    bool m_esCaptura;
    int m_numCaptures;
};

#endif