#pragma once

/**
* FITXER moviment.h
* AUTOR Jennifer Martinez | Francois Liraud
* DATA 10/04/2025
* VERSIO 1.0
* Aquest fitxer conte les funcions de la classe Moviment.h
*/

#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "posicio.hpp"
#include <vector>
using namespace std;

/**
* CLASS Moviment
* Classe que representa un moviment d'una fitxa al tauler de dames.
* 
* Els seus atributs son:
* - m_posicions: array de posicions que representa el moviment.
* - m_numPosicions: numero de posicions del moviment.
* - m_esCaptura: boolea que indica si el moviment es de captura.
* - m_numCaptures: numero de captures del moviment.
*/

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
    void estableixPosicions(const vector<Posicio>& m_posicions);
    bool contePosicio(const Posicio& posicio) const;

	void printPosicions() const;
private:
	vector<Posicio> m_posicions;
    bool m_esCaptura;
    int m_numCaptures;
};

#endif