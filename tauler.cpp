#include "Tauler.h"
#include <fstream>
using namespace std;
/**
* FITXER tauler.cpp
* AUTOR Jennifer Martínez
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

void Tauler::inicialitza(const string& nomFitxer) {
    ifstream fitxer(nomFitxer);
    if (!fitxer.is_open()) {
        return;
    }

    char linia[100];
    while (fitxer.getline(linia, 100)) {
        char tipusStr[10] = { 0 };
        char posicioStr[10] = { 0 };
        int currentPos = 0;
        int destPos = 0;

        while (linia[currentPos] == ' ' || linia[currentPos] == '\t') currentPos++;

        while (linia[currentPos] != '\0' && linia[currentPos] != ' ' &&
            linia[currentPos] != '\t' && linia[currentPos] != '\n' &&
            destPos < 9) {
            tipusStr[destPos++] = linia[currentPos++];
        }
        tipusStr[destPos] = '\0';

        destPos = 0;
        while (linia[currentPos] == ' ' || linia[currentPos] == '\t') currentPos++;

        while (linia[currentPos] != '\0' && linia[currentPos] != ' ' &&
            linia[currentPos] != '\t' && linia[currentPos] != '\n' &&
            destPos < 9) {
            posicioStr[destPos++] = linia[currentPos++];
        }
        posicioStr[destPos] = '\0';

        if (tipusStr[0] != '\0' && posicioStr[0] != '\0') {
            Posicio pos(posicioStr);
            TipusFitxa tipus = TIPUS_EMPTY;
            ColorFitxa color = COLOR_BLANC;

            switch (tipusStr[0]) {
            case 'O':
                tipus = TIPUS_NORMAL;
                color = COLOR_BLANC;
                break;
            case 'X':
                tipus = TIPUS_NORMAL;
                color = COLOR_NEGRE;
                break;
            case 'D':
                tipus = TIPUS_DAMA;
                color = COLOR_BLANC;
                break;
            case 'R':
                tipus = TIPUS_DAMA;
                color = COLOR_NEGRE;
                break;
            default:
                continue;
            }

            int fila = pos.getFila() - 1;
            int col = pos.getColumna();
            if (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES) {
                m_tauler[fila][col] = Fitxa(tipus, color, pos);
            }
        }
    }
}

void Tauler::actualitzaMovimentsValids() {
    for (int i = 0; i < N_FILES; ++i) {
        for (int j = 0; j < N_COLUMNES; ++j) {
            if (m_tauler[i][j].getTipus() != TIPUS_EMPTY) {
                m_tauler[i][j].netejaMovimentsValids();

                Posicio posActual(i + 1, j);
                Moviment moviments[MAX_MOVIMENTS];
                int numMoviments = 0;

                for (int k = 0; k < numMoviments; k++) {
                    m_tauler[i][j].afegeixMovimentValid(moviments[k]);
                }
            }
        }
    }
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) {
    nPosicions = 0;
    if (origen.getFila() < 1 || origen.getFila() > N_FILES ||
        origen.getColumna() < 0 || origen.getColumna() >= N_COLUMNES) {
        return;
    }

    int fila = origen.getFila() - 1;
    int col = origen.getColumna();

    if (m_tauler[fila][col].getTipus() == TIPUS_EMPTY) return;

    for (int i = 0; i < m_tauler[fila][col].getNumMovimentsValids(); ++i) {
        const Moviment& mov = m_tauler[fila][col].getMovimentValid(i);
        const Posicio& posFinal = mov.getPosicioFinal();
        bool trobada = false;

        for (int j = 0; j < nPosicions; ++j) {
            if (posicionsPossibles[j] == posFinal) {
                trobada = true;
                break;
            }
        }

        if (!trobada) {
            posicionsPossibles[nPosicions++] = posFinal;
        }
    }
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) {
    if (origen.getFila() < 1 || origen.getFila() > N_FILES ||
        origen.getColumna() < 0 || origen.getColumna() >= N_COLUMNES ||
        desti.getFila() < 1 || desti.getFila() > N_FILES ||
        desti.getColumna() < 0 || desti.getColumna() >= N_COLUMNES) {
        return false;
    }

    int filaOrigen = origen.getFila() - 1;
    int colOrigen = origen.getColumna();

    if (m_tauler[filaOrigen][colOrigen].getTipus() == TIPUS_EMPTY) return false;

    bool movimentValid = false;

    for (int i = 0; i < m_tauler[filaOrigen][colOrigen].getNumMovimentsValids(); ++i) {
        const Moviment& mov = m_tauler[filaOrigen][colOrigen].getMovimentValid(i);
        if (mov.getPosicioFinal() == desti) {
            movimentValid = true;
            break;
        }
    }

    if (!movimentValid) return false;

    int filaDesti = desti.getFila() - 1;
    int colDesti = desti.getColumna();

    ColorFitxa color = m_tauler[filaOrigen][colOrigen].getColor();
    TipusFitxa tipus = m_tauler[filaOrigen][colOrigen].getTipus();

    m_tauler[filaDesti][colDesti] = m_tauler[filaOrigen][colOrigen];
    m_tauler[filaDesti][colDesti].setPosicio(desti);
    m_tauler[filaOrigen][colOrigen] = Fitxa();

    if ((desti.getFila() == 1 && color == COLOR_BLANC) ||
        (desti.getFila() == 8 && color == COLOR_NEGRE)) {
        m_tauler[filaDesti][colDesti].convertirADama();
    }

    actualitzaMovimentsValids();

    return true;
}

string Tauler::toString() const {
    string result;

    for (int i = N_FILES - 1; i >= 0; --i) {
        result += std::to_string(i + 1) + ": ";

        for (int j = 0; j < N_COLUMNES; ++j) {
            TipusFitxa tipus = m_tauler[i][j].getTipus();
            ColorFitxa color = m_tauler[i][j].getColor();

            if (tipus == TIPUS_EMPTY) {
                result += "_";
            }
            else {
                if (tipus == TIPUS_DAMA) {
                    result += (color == COLOR_BLANC) ? "D" : "R";
                }
                else {
                    result += (color == COLOR_BLANC) ? "O" : "X";
                }
            }

            if (j < N_COLUMNES - 1) {
                result += " ";
            }
        }

        if (i > 0) {
            result += "\n";
        }
    }

    return result;
}