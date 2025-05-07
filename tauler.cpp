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

Tauler::Tauler() 
{
    for (int i = 0; i < N_FILES; ++i) 
    {
        for (int j = 0; j < N_COLUMNES; ++j) 
        {
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
            fitxa.setPosicio(Posicio(i + 1, j));

            if (fitxa.getTipus() != TIPUS_EMPTY)
            {
                fitxa.resetMovimentsValids();
                calculaMovimentsFitxa(i, j);
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

    int fila = origen.getFila() - 1;
    int col = origen.getColumna();

    if (esDinsTauler(fila, col))
    {
        const Fitxa& fitxa = m_tauler[fila][col];

        if (fitxa.getTipus() != TIPUS_EMPTY)
        {
            for (int i = 0; i < fitxa.getNumMovimentsValids(); ++i)
            {
                const Moviment& mov = fitxa.getMovimentValid(i);

                // Para movimientos de captura, añadir todas las posiciones intermedias
                if (mov.getEsMovimentDeCaptura())
                {
                    for (int p = 1; p < mov.getNumPosicions(); ++p)
                    {
                        const Posicio& posIntermedia = mov.getPosicio(p);

                        // Evitar duplicados
                        bool trobada = false;
                        for (int j = 0; j < nPosicions && !trobada; ++j)
                        {
                            if (posicionsPossibles[j] == posIntermedia)
                                trobada = true;
                        }

                        if (!trobada)
                            posicionsPossibles[nPosicions++] = posIntermedia;
                    }
                }
                else // Para movimientos simples, solo añadir la posición final
                {
                    const Posicio& posFinal = mov.getPosicioFinal();

                    // Evitar duplicados
                    bool trobada = false;
                    for (int j = 0; j < nPosicions && !trobada; ++j)
                    {
                        if (posicionsPossibles[j] == posFinal)
                            trobada = true;
                    }

                    if (!trobada)
                        posicionsPossibles[nPosicions++] = posFinal;
                }
            }
        }
    }       
}


/*
* esDinsTauler
* Funcio auxiliar que comprova si una posicio es valida dins del tauler.
*  
* @param fila: int, fila de la posicio
* @param col: int, columna de la posicio
* @return bool: retorna si la posicio es valida o no.
*/
bool Tauler::esDinsTauler(int fila, int col) const
{
    return fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES;
}

/**
* getCapturesDama
* Funcio auxiliar que busca les captures disponibles per una dama.
* 
* @param fitxa: Tipus Fitxa, es la fitxa que volem moure
* @param movActual: Tipus Moviment, es el moviment actual que volem fer
* @param pendents[]: Tipus Moviment, es l'array de moviments pendents
* @param numPendents: int, es el numero de moviments pendents
* @return void
*/
void Tauler::getCapturesDama(const Fitxa& fitxa, const Moviment& movActual, Moviment pendents[], int& numPendents)
{
	// Direccions possibles per a la dama (diagonal)
	// avall-dreta, avall-esquerra, amunt-dreta, amunt-esquerra
    const int dirs[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
    Posicio pos = movActual.getPosicioFinal();
    int fila = pos.getFila() - 1;
    int col = pos.getColumna();

	// Comprovar si hi ha captures possibles en cada direccio
    for (int d = 0; d < 4; ++d)
    {
		// Direccio actual, delta fila, delta columna
        int df = dirs[d][0];
        int dc = dirs[d][1];

		// Comencem a buscar la primera fitxa enemiga
        // Posicions d'exploracio
        int f = fila + df;
        int c = col + dc;

        bool trobatEnemic = false;
        int filaEnemic = -1, colEnemic = -1;
        bool sortirbucle = false;

		// Busquem la primera fitxa enemiga
        while (esDinsTauler(f, c) && !sortirbucle)
        {
            const Fitxa& actual = m_tauler[f][c];

            if (!trobatEnemic)
            {
                if (actual.getTipus() != TIPUS_EMPTY && actual.getColor() != fitxa.getColor())
                {
                    trobatEnemic = true;
                    filaEnemic = f;
                    colEnemic = c;
                }
                else if (actual.getTipus() != TIPUS_EMPTY)
                {
                    sortirbucle = true;
                }
            }
            else
            {
                if (actual.getTipus() == TIPUS_EMPTY)
                {
                    Moviment nou = movActual;
                    nou.setEsMovimentDeCaptura(true);
                    nou.afegeixPosicio(Posicio(f + 1, c));

                    Fitxa original = m_tauler[filaEnemic][colEnemic];
                    m_tauler[filaEnemic][colEnemic] = Fitxa();

                    getCapturesDama(fitxa, nou, pendents, numPendents);

                    m_tauler[filaEnemic][colEnemic] = original;

                    if (nou.getNumPosicions() > movActual.getNumPosicions())
                        pendents[numPendents++] = nou;x
                }
                else
                {
                    sortirbucle = true;
                }
            }
            if (!sortirbucle)
            {
				f += df;
				c += dc;
            }
        }
    }
}


/*
* getCapturesDisponibles
* Funcio auxiliar que busca les captures disponibles per una fitxa normal.
* 
* @param fitxa: Tipus Fitxa, es la fitxa que volem moure
* @param movActual: Tipus Moviment, es el moviment actual que volem fer
* @param pendents[]: Tipus Moviment, es l'array de moviments pendents
* @param numPendents: int, es el numero de moviments pendents
* @return void
*/
void Tauler::getCapturesDisponibles(const Fitxa& fitxa, const Moviment& movActual, Moviment pendents[], int& numPendents)
{
    const int dirs[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
    Posicio pos = movActual.getPosicioFinal();
    int fila = pos.getFila() - 1;
    int col = pos.getColumna();

    for (int i = 0; i < 4; ++i) 
    {
        int fmid = fila + dirs[i][0];
        int cmid = col + dirs[i][1];
        int fdest = fmid + dirs[i][0];
        int cdest = cmid + dirs[i][1];

        if (esDinsTauler(fmid, cmid) && esDinsTauler(fdest, cdest)) 
        {
            const Fitxa& interm = m_tauler[fmid][cmid];
            const Fitxa& desti = m_tauler[fdest][cdest];
            if (interm.getTipus() != TIPUS_EMPTY && interm.getColor() != fitxa.getColor() && desti.getTipus() == TIPUS_EMPTY) 
            {
                if (numPendents < MAX_MOVIMENTS && movActual.getNumPosicions() < MAX_POSICIONS - 1) 
                {
                    Moviment nou = movActual;
                    nou.setEsMovimentDeCaptura(true);
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
	bool valid = true;

    if (!esDinsTauler(filaOrig, colOrig))
    {
        valid = false;

    }
    else
    {
        Fitxa& fitxaOrig = m_tauler[filaOrig][colOrig];

        if (fitxaOrig.getTipus() == TIPUS_EMPTY)
        {
            valid = false;
        }
        else
        {
            // Actualizamos movimientos
            actualitzaMovimentsValids();

            // Buscar movimiento válido para esta ficha
            const Fitxa& fitxa = m_tauler[filaOrig][colOrig];
            int indexMov = -1;

            for (int i = 0; i < fitxa.getNumMovimentsValids(); ++i)
            {
                if (fitxa.getMovimentValid(i).getPosicioFinal() == desti)
                {
                    indexMov = i;
                }
            }

            // No es movimiento válido
            if (indexMov == -1)
            {
                valid = false;
            }
            else
            {
                const Moviment& mov = fitxa.getMovimentValid(indexMov);

                // Verificamos si hay capturas posibles globalmente
                bool hiHaCaptura = false;
                for (int i = 0; i < N_FILES; ++i)
                {
                    for (int j = 0; j < N_COLUMNES; ++j)
                    {
                        const Fitxa& f = m_tauler[i][j];
                        if (f.getTipus() != TIPUS_EMPTY && f.getColor() == fitxaOrig.getColor())
                        {
                            for (int k = 0; k < f.getNumMovimentsValids(); ++k)
                            {
                                if (f.getMovimentValid(k).getEsMovimentDeCaptura())
                                    hiHaCaptura = true;
                            }
                        }
                    }
                }

                // Si hay capturas posibles y no es de captura => BUFAR
                if (hiHaCaptura && !mov.getEsMovimentDeCaptura())
                {
                    m_tauler[filaOrig][colOrig] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, origen);
                    valid = true;
                }
                else
                {
                    // Ejecutar captura
                    if (mov.getEsMovimentDeCaptura())
                    {
                        for (int i = 1; i < mov.getNumPosicions(); ++i)
                        {
                            int f1 = mov.getPosicio(i - 1).getFila() - 1;
                            int c1 = mov.getPosicio(i - 1).getColumna();
                            int f2 = mov.getPosicio(i).getFila() - 1;
                            int c2 = mov.getPosicio(i).getColumna();

                            int filaCap = (f1 + f2) / 2;
                            int colCap = (c1 + c2) / 2;

                            m_tauler[filaCap][colCap] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, Posicio(filaCap + 1, colCap));
                        }
                    }

                    // Mover la ficha
                    int filaDest = desti.getFila() - 1;
                    int colDest = desti.getColumna();
                    m_tauler[filaDest][colDest] = fitxaOrig;
                    m_tauler[filaDest][colDest].setPosicio(desti);
                    m_tauler[filaOrig][colOrig] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, origen);

                    // Promoción si corresponde
                    if ((m_tauler[filaDest][colDest].getColor() == COLOR_BLANC && filaDest == 7) ||
                        (m_tauler[filaDest][colDest].getColor() == COLOR_NEGRE && filaDest == 0))
                    {
                        m_tauler[filaDest][colDest].convertirADama();
                    }
					// Actualizar movimientos válidos de la ficha que se ha movido
                    // Si arriba fins a aqui, valid = true, el moviment sera valid
                }
            }
        }      
    }
}

/*
* calculaMovimentsFitxa
* Funcio que calcula els moviments possibles d'una fitxa.
* 
* @param fila: int, fila de la fitxa
* @param col: int, columna de la fitxa
* @return void
*/
void Tauler::calculaMovimentsFitxa(int fila, int col)
{
    if (esDinsTauler(fila, col))
    {
        Fitxa& fitxa = m_tauler[fila][col];
        Posicio origen = fitxa.getPosicio();

        Moviment pendents[MAX_MOVIMENTS];
        int numPendents = 0;

        if (numPendents < MAX_MOVIMENTS)
            pendents[numPendents++] = Moviment(origen);

        bool hiHaCaptures = false;

        // Primero calculamos todas las capturas posibles
        while (numPendents > 0)
        {
            Moviment actual = pendents[--numPendents];
            int anteriorNum = numPendents;

            if (fitxa.getTipus() == TIPUS_DAMA)
                getCapturesDama(fitxa, actual, pendents, numPendents);
            else
                getCapturesDisponibles(fitxa, actual, pendents, numPendents);

            if (numPendents == anteriorNum && actual.getNumPosicions() > 1)
            {
                actual.setEsMovimentDeCaptura(true);
                fitxa.afegeixMovimentValid(actual);
                hiHaCaptures = true;
            }
        }

        // Para fichas normales
        if (fitxa.getTipus() == TIPUS_NORMAL)
        {
            int dir;
            if (fitxa.getColor() == COLOR_BLANC) {
                dir = 1;
            }
            else {
                dir = -1;
            }
            for (int dc = -1; dc <= 1; dc += 2)
            {
                int nf = fila + dir;
                int nc = col + dc;
                if (esDinsTauler(nf, nc) && m_tauler[nf][nc].getTipus() == TIPUS_EMPTY)
                {
                    Moviment m(origen);
                    m.afegeixPosicio(Posicio(nf + 1, nc));
                    fitxa.afegeixMovimentValid(m);
                }
            }
        }
        else if (fitxa.getTipus() == TIPUS_DAMA)
        {
            const int dirs[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
            for (int d = 0; d < 4; ++d)
            {
                int df = dirs[d][0];
                int dc = dirs[d][1];
                int nf = fila + df;
                int nc = col + dc;

                // Movimientos simples de una casilla (incluyendo hacia atrás)
                if (esDinsTauler(nf, nc) && m_tauler[nf][nc].getTipus() == TIPUS_EMPTY)
                {
                    Moviment m(origen);
                    m.afegeixPosicio(Posicio(nf + 1, nc));
                    fitxa.afegeixMovimentValid(m);
                }

                // Movimientos múltiples
                while (esDinsTauler(nf, nc) && m_tauler[nf][nc].getTipus() == TIPUS_EMPTY)
                {
                    Moviment m(origen);
                    m.afegeixPosicio(Posicio(nf + 1, nc));
                    fitxa.afegeixMovimentValid(m);
                    nf += df;
                    nc += dc;
                }
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
