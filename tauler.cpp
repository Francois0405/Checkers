#include "tauler.hpp"

#include <fstream>
#include <iostream>

using namespace std;
/**
* FITXER tauler.cpp
* AUTOR Jennifer Martinez | Francois Liraud
* DATA 10/04/2025
* VERSIO 1.1
* Aquest fitxer conte les funcions de la classe Tauler.cpp
*/

/*
* Tauler
* Constructor per defecte, inicialitza el tauler a empty "de color blanc" (empty).
* No hi ha cap fitxa en el tauler.
*/

Tauler::Tauler() {
    for (int i = 0; i < N_FILES; ++i) {
        for (int j = 0; j < N_COLUMNES; ++j) {
            m_tauler[i][j] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, Posicio(i + 1, j));
        }
    }
}

/*
* inicialitza
* Inicialitza el tauler des de un arxiu.
*
* @param nomFitxer: nom del Fitxer del qual extreiem el tauler.
* @return void
*/

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

/*
* actualitzaMovimentsValids
* Actualitza els moviments valids de totes les peces del joc i les guarda en fitxa -> movimentsValids[]
* un array de Moviment.
*
* @return void
*/

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
                else // Color negre
                    direccio = -1; //determina direccio de las fitxes segons el color

                int filaActual = i;
                int colActual = j;

                // Amb aquest for, farem dues iteracions, una a -1 i una altre a 1. (les dues caselles diagonals)
                for (int dCol = -1; dCol <= 1; dCol += 2)
                {
                    int filaNova = filaActual + direccio;
                    int colNova = colActual + dCol; // dreta o esquerra.
                    if (filaNova >= 0 && filaNova < N_FILES && colNova >= 0 && colNova < N_COLUMNES)
                    {
                        if (m_tauler[filaNova][colNova].getTipus() == TIPUS_EMPTY)
                        {
                            Moviment mov(fitxa.getPosicio());
                            mov.setEsMovimentDeCaptura(true);
                            mov.afegeixPosicio(Posicio(filaNova + 1, colNova));
                            fitxa.afegeixMovimentValid(mov);
                        }
                        else if ((m_tauler[filaNova][colNova].getColor() == COLOR_BLANC) && (direccio == -1) ||
                            (m_tauler[filaNova][colNova].getColor() == COLOR_NEGRE) && (direccio == 1))
                        {
							filaNova += direccio; // Vamos una mas para abajo
							colNova += dCol; // Dreta o esquerra
                            if (filaNova >= 0 && filaNova < N_FILES && colNova >= 0 && colNova < N_COLUMNES)
                            {
								if (m_tauler[filaNova][colNova].getTipus() == TIPUS_EMPTY)
								{
									Moviment mov(fitxa.getPosicio());
									mov.setEsMovimentDeCaptura(true);
									mov.afegeixPosicio(Posicio(filaNova + 1, colNova));
									fitxa.afegeixMovimentValid(mov);
								}
                            }
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

/*
* getPosicionsPossibles
* Getters que retorna l'array de posicions valides d'una fitxa d'un punt origen.
*
* @param origen: Tipus Posicio, es el punt on es troba la fitxa actualment
* @param nPosicions: int, ens diu el numero de posicions valides
* @param posicionsPossibles[]: Tipus Posicio ens dona les posicions possibles de la fitxa
* @return void
*/

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
    nPosicions = 0;

    //verifiquem que la posicio d'origen es dins del tauler
    if (origen.getFila() >= 1 && origen.getFila() <= N_FILES && origen.getColumna() >= 0 && origen.getColumna() < N_COLUMNES)
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

// Auxiliar: comprova si una posici  est  dins del tauler
//FALTA POSAR COMNETARI BE
bool Tauler::esDinsTauler(int fila, int col) const
{
    return fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES;
}

//FALTA COMENTARIO BIEN
// Auxiliar: captura per dama
void Tauler::getCapturesDama(const Fitxa& fitxa, const Moviment& movActual, Moviment pendents[], int& numPendents)
{
    const int dirs[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
    Posicio pos = movActual.getPosicioFinal();
    int fila = pos.getFila() - 1;
    int col = pos.getColumna();

    for (int d = 0; d < 4; ++d)
    {
        int df = dirs[d][0];
        int dc = dirs[d][1];
        int f = fila + df;
        int c = col + dc;

        bool trobatEnemic = false;
        //int fEnemic = -1, cEnemic = -1;
        bool sortir = false;

        while (!sortir && esDinsTauler(f, c)) {
            const Fitxa& actual = m_tauler[f][c];

            if (!trobatEnemic) {
                if (actual.getTipus() != TIPUS_EMPTY && actual.getColor() != fitxa.getColor()) {
                    trobatEnemic = true;
                }
                else if (actual.getTipus() != TIPUS_EMPTY) {
                    sortir = true;
                }
            }
            else {
                if (actual.getTipus() == TIPUS_EMPTY) {
                    if (numPendents < MAX_MOVIMENTS && movActual.getNumPosicions() < MAX_POSICIONS - 1) {
                        Moviment nou = movActual;
                        nou.afegeixPosicio(Posicio(f + 1, c));
                        pendents[numPendents++] = nou;
                    }
                }
                else {
                    sortir = true;
                }
            }

            f += df;
            c += dc;
        }
    }
}

//FALTA COMENTARIO BIEN
void Tauler::getCapturesDisponibles(const Fitxa& fitxa, const Moviment& movActual, Moviment pendents[], int& numPendents)
{
    const int dirs[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
    Posicio pos = movActual.getPosicioFinal();
    int fila = pos.getFila() - 1;
    int col = pos.getColumna();

    for (int i = 0; i < 4; ++i) {
        int fmid = fila + dirs[i][0];
        int cmid = col + dirs[i][1];
        int fdest = fmid + dirs[i][0];
        int cdest = cmid + dirs[i][1];

        if (esDinsTauler(fmid, cmid) && esDinsTauler(fdest, cdest)) {
            const Fitxa& interm = m_tauler[fmid][cmid];
            const Fitxa& desti = m_tauler[fdest][cdest];

            if (interm.getTipus() != TIPUS_EMPTY && interm.getColor() != fitxa.getColor() && desti.getTipus() == TIPUS_EMPTY) {
                if (numPendents < MAX_MOVIMENTS && movActual.getNumPosicions() < MAX_POSICIONS - 1) {
                    Moviment nou = movActual;
                    nou.afegeixPosicio(Posicio(fdest + 1, cdest));
                    pendents[numPendents++] = nou;
                }
            }
        }
    }
}


/*
* mouFitxa
* Funci  que mou la fitxa i gestiona el que pot passar durant el seu moviment (si mata o no)
* primer comprova si la posicio que es vol accedir es valida per la fitxa seleccionada. Si no es possible
* retorna false.
*
* @param origen: Tipus Posicio, es el punt on es troba la fitxa actualment
* @param desti: Tipus Posicio, es el punt on vol anar aquesta fitxa.
* @return bool: Retorna si el moviment s'ha pogut realitzar o no.
*/

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

//FALTA PONER COMENATARIO BIEN
// Auxiliar: calcula tots els moviments (captures encadenades o simples) d'una fitxa
void Tauler::calculaMovimentsFitxa(int fila, int col) {
    if (!esDinsTauler(fila, col)) return;

    Fitxa& fitxa = m_tauler[fila][col];
    Posicio origen = fitxa.getPosicio();

    Moviment pendents[MAX_MOVIMENTS];
    int numPendents = 0;

    if (numPendents < MAX_MOVIMENTS)
    {
        // Creem un nou moviment des de l'origen
        pendents[numPendents++] = Moviment(origen);
    }

    while (numPendents > 0) 
    {
        Moviment actual = pendents[--numPendents];
        Posicio posAct = actual.getPosicioFinal();

        int anteriorNum = numPendents;

        if (fitxa.getTipus() == TIPUS_DAMA)
            getCapturesDama(fitxa, actual, pendents, numPendents);
        else
            getCapturesDisponibles(fitxa, actual, pendents, numPendents);

        if (numPendents == anteriorNum && actual.getNumPosicions() > 1) {
            fitxa.afegeixMovimentValid(actual);
        }
    }

    if (fitxa.getNumMovimentsValids() == 0 && fitxa.getTipus() == TIPUS_NORMAL) {
        int dir = (fitxa.getColor() == COLOR_BLANC) ? 1 : -1;

        for (int dc = -1; dc <= 1; dc += 2) {
            int nf = fila + dir;
            int nc = col + dc;
            if (esDinsTauler(nf, nc) && m_tauler[nf][nc].getTipus() == TIPUS_EMPTY) {
                Moviment m(fitxa.getPosicio());
                m.afegeixPosicio(Posicio(nf + 1, nc));
                fitxa.afegeixMovimentValid(m);
            }
        }
    }
}


/*
* toString
* Genera un string amb l estat actual del tauler de joc. Cerquem extreure m_tauler a
* '-' Casella buida
* 'O' Normal Blanca
* 'X' Normal Negra
* 'D' Dama Blanca
* 'R' Reina Negra
*
* EXEMPLE:
    8: _ X _ D _ _ _ X
    7: _ _ _ _ _ _ X _
    6: _ _ _ _ _ _ _ _
    5: R _ _ _ _ _ _ _
    4: _ _ _ _ _ _ _ O
    3: _ _ O _ _ _ O _
    2: _ O _ _ _ _ _ X
    1: O _ O _ D _ _ _
       A B C D E F G H
*
* @return string: Estat actual del tauler.
*/
string Tauler::toString() const
{
    string taulerString;
    int fila = 8;
    for (int i = N_FILES - 1; i >= 0; i--) // Files (numeros)
    {
        taulerString += to_string(fila);
        taulerString += ": ";
        for (int j = 0; j < N_COLUMNES; j++) // Columnes (lletres)
        {
            taulerString += m_tauler[i][j].getLletra();
            taulerString += " ";
        }
        taulerString += "\n";
        fila--;
    }
    taulerString += "   a b c d e f g h";
    return taulerString;
}
