#include "Tauler.h"
#include <fstream>
using namespace std;
/**
* FITXER tauler.cpp
* AUTOR Jennifer Martínez | François Liraud
* DATA 10/04/2025
* VERSIO 1.1
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
    ifstream fitxer(nomFitxer);
    if (fitxer.is_open())
    {
        char tipus;
        string posicioStr;
        while (fitxer >> tipus >> posicioStr)
        {
            Posicio posicio(posicioStr);
            int fila = posicio.getFila() - 1;
            int col = posicio.getColumna();

            TipusFitxa tipusFitxa;
            ColorFitxa color;

            switch (tipus) {
            case 'O':
                tipusFitxa = TIPUS_NORMAL;
                color = COLOR_BLANC;
                break;
            case 'X':
                tipusFitxa = TIPUS_NORMAL;
                color = COLOR_NEGRE;
                break;
            case 'D':
                tipusFitxa = TIPUS_DAMA;
                color = COLOR_BLANC;
                break;
            case 'R':
                tipusFitxa = TIPUS_DAMA;
                color = COLOR_NEGRE;
                break;
            default:
                tipusFitxa = TIPUS_EMPTY;
                color = COLOR_BLANC;
                break;
            }
            m_tauler[fila][col] = Fitxa(tipusFitxa, color, posicio);
        }
    }
    fitxer.close();
}

void Tauler::actualitzaMovimentsValids() 
{
    for (int i = 0; i < N_FILES; ++i) 
    {
        for (int j = 0; j < N_COLUMNES; ++j) 
        {
            Fitxa& fitxa = m_tauler[i][j];
            fitxa.setPosicio(Posicio(i + 1, j)); //agafa referencia de la fitxa i comproba que sigui correcta la seva posicio

            if (fitxa.getTipus() != TIPUS_EMPTY) //nomes si no estan buidas
            {
                int direccio;
                if (fitxa.getColor() == COLOR_BLANC)
                    direccio = 1;
                else
                    direccio = -1; //determina direccio de las fitxes segons el color

                int filaActual = i;
                int colActual = j;
                int filaNova = filaActual + direccio;

                for (int dCol = -1; dCol <= 1; dCol += 2) 
                {
                    int colNova = colActual + dCol;
                    if (filaNova >= 0 && filaNova < N_FILES && colNova >= 0 && colNova < N_COLUMNES) 
                    {
                        if (m_tauler[filaNova][colNova].getTipus() == TIPUS_EMPTY) 
                        {
                            Moviment mov(fitxa.getPosicio());
                            mov.afegeixPosicio(Posicio(filaNova + 1, colNova));
                            fitxa.afegeixMovimentValid(mov);
                        }
                    }
                }
            }
            else 
            {
                fitxa = Fitxa(TIPUS_EMPTY, COLOR_BLANC, Posicio(i + 1, j));
            }
        }
    }
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) 
{
    nPosicions = 0;
    if (origen.getFila() >= 1 && origen.getFila() <= N_FILES && origen.getColumna() >= 0 && origen.getColumna() < N_COLUMNES) //verifiquem que la posicio d'origen es dins del tauler
    {

        int fila = origen.getFila() - 1;
        int col = origen.getColumna();

        const Fitxa& fitxa = m_tauler[fila][col];

        if (fitxa.getTipus() != TIPUS_EMPTY) 
        {
            for (int i = 0; i < fitxa.getNumMovimentsValids(); ++i) 
            {
                const Moviment& mov = fitxa.getMovimentValid(i);
                const Posicio& posFinal = mov.getPosicioFinal();
                bool trobada = false;

                for (int j = 0; j < nPosicions && !trobada; ++j) 
                {
                    if (posicionsPossibles[j] == posFinal) 
                    {
                        trobada = true;
                    }
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
    int filaOrig = origen.getFila() - 1;
    int colOrig = origen.getColumna();

    Fitxa& fitxaOrig = m_tauler[filaOrig][colOrig];

    if (fitxaOrig.getTipus() == TIPUS_EMPTY) //si la casella esta buida no es pot moure res
        return false;

    bool movimentValid = false;
    int i = 0;
    while (i < fitxaOrig.getNumMovimentsValids() && !movimentValid) //per comprobar si el moviment es valid, sino retorna false
    {
        if (fitxaOrig.getMovimentValid(i).getPosicioFinal() == desti)
        {
            movimentValid = true;
        }
        ++i;
    }

    if (!movimentValid) //si no es valid no s'executa el moviment
        return false;

    int filaDest = desti.getFila() - 1;
    int colDest = desti.getColumna(); //transforma desti en indexs de l'array

    m_tauler[filaDest][colDest] = fitxaOrig;
    m_tauler[filaDest][colDest].setPosicio(desti);//actualitza posicio

    m_tauler[filaOrig][colOrig] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, origen); //casella original ara buida

    if ((m_tauler[filaDest][colDest].getColor() == COLOR_BLANC && filaDest == 7) || (m_tauler[filaDest][colDest].getColor() == COLOR_NEGRE && filaDest == 0)) 
    {
        m_tauler[filaDest][colDest].convertirADama(); //si la fitxa arriba al final es converteix en dama
    }

    return true;
}

string Tauler::toString() const 
{
    string str = "aaa";

    return str;
}