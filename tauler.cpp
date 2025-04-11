#include "Tauler.h"
#include <fstream>
using namespace std;
/**
* FITXER tauler.cpp
* AUTOR Jennifer Martínez | François Liraud
* DATA 10/04/2025
* VERSIO 1.0
* Aquest fitxer conté les funcions de la classe Tauler.cpp
*/

Tauler::Tauler() {
    for (int i = 0; i < N_FILES; ++i) {
        for (int j = 0; j < N_COLUMNES; ++j) {
            m_tauler[i][j] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, Posicio(i + 1, j));
        }
    }
}

void Tauler::inicialitza(const string& nomFitxer) 
{
    
}

void Tauler::actualitzaMovimentsValids() 
{
   
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) {
    nPosicions = 0;
    if (origen.getFila() < 1 || origen.getFila() > N_FILES ||
        origen.getColumna() < 0 || origen.getColumna() >= N_COLUMNES) 
    {
    }
    else
    {
        int fila = origen.getFila() - 1;
        int col = origen.getColumna();

        if (m_tauler[fila][col].getTipus() != TIPUS_EMPTY)
        {
            int j = 0;
            for (int i = 0; i < m_tauler[fila][col].getNumMovimentsValids(); ++i)
            {
                const Moviment& mov = m_tauler[fila][col].getMovimentValid(i);
                const Posicio& posFinal = mov.getPosicioFinal();
                bool trobada = false;

                while (j < nPosicions && !false)
                {
                    if (posicionsPossibles[j] == posFinal)
                    {
                        trobada = true;
                    }
                    j++;
                }

                if (!trobada)
                {
                    posicionsPossibles[nPosicions++] = posFinal;
                }
            }
        }
    }   
}


bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) 
{
    return true;
}

string Tauler::toString() const 
{
    string str = "aaa";

    return str;
}