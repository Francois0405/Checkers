#include "tauler.hpp"
#include <fstream>
#include <iostream>
#include "GraphicManager.h"
#include "info_joc.hpp"

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
    cout << endl << "[DEBUG] Tauler() Correcte" << endl;
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
    cout << "[DEBUG] Intentant obrir fitxer: " << nomFitxer << endl;
    ifstream fitxer(nomFitxer);

    string linia;
    cout << "[DEBUG] Contingut del fitxer:" << endl;
    while (getline(fitxer, linia)) {
        cout << linia << endl;
    }
    fitxer.clear();                 // Reseteja flags (EOF, failbit)
    fitxer.seekg(0, ios::beg);

    if (fitxer.is_open())
    {
        char tipus;
        string posicioStr;
        while (fitxer >> tipus >> posicioStr)
        {

            Posicio posicio(posicioStr);
            int fila = posicio.getFila();
            int col = posicio.getColumna();
            cout << " - Inicialitzant a (row:" << fila << ", col:" << col
                << ") per la posicio: " << posicioStr << endl;
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
        cout << endl << "[DEBUG] inicialitza() Correcte" << endl;
        fitxer.close();
    }
    else
    {
        // Llança un error que atura l'execucio
        cout << "[ERROR] inicialitza()      Fitxer no trobat";
        throw runtime_error("ERROR: Fitxer no trobat");
    }
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
            // Se busca actualizar todasx las piezas del juego, por lo tanto, cojemos cada fitxa.
            Fitxa& fitxa = m_tauler[i][j];
            // Setter de Posicio (atributo)
            fitxa.setPosicio(Posicio(i, j));

            // Solo calculamos los movimientos de fitxas, no casillas vacias
            if (fitxa.getTipus() != TIPUS_EMPTY)
            {
                fitxa.resetMovimentsValids();
                // Calculamos los movimientos de la ficha fil i, col j
                calculaMovimentsFitxa(i, j);
            }
        }
    }
    cout << endl << "[DEBUG] actualitzaMovimentsValids() Correcte" << endl;
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

void Tauler::getPosicionsPossibles(const Posicio& origen, vector<Posicio>& posicionsPossibles) {
    posicionsPossibles.clear();
    int fila = origen.getFila();  // 0-7
    int col = origen.getColumna(); // 0-7

    if (esDinsTauler(fila, col)) {
        const Fitxa& fitxa = m_tauler[fila][col];

        if (fitxa.getTipus() != TIPUS_EMPTY) {
            // Directions: [df, dc]
            int dirsDama[4][2] = { {-1, 1}, {-1, -1}, {1, 1}, {1, -1} }; // All 4 diagonals for damas

            if (fitxa.getTipus() == TIPUS_NORMAL) {
                // For normal pieces, only 2 possible directions (forward diagonals)
                int dir = (fitxa.getColor() == COLOR_BLANC) ? -1 : 1; // White up (-1), black down (+1)
                int dirsNormal[2][2] = { {dir, 1}, {dir, -1} };

                for (int d = 0; d < 2; ++d) {
                    int f = fila + dirsNormal[d][0];
                    int c = col + dirsNormal[d][1];

                    if (esDinsTauler(f, c))
                    {
                        if (m_tauler[f][c].getTipus() == TIPUS_EMPTY) 
                        {
                            posicionsPossibles.push_back(Posicio(f, c));
                        }
                    }
                }
            }
            else if (fitxa.getTipus() == TIPUS_DAMA) {
                // Dama movement (all 4 diagonals until obstacle)
                for (int d = 0; d < 4; ++d) {
                    int f = fila + dirsDama[d][0];
                    int c = col + dirsDama[d][1];
                    bool trobatObstacle = false;

                    while (esDinsTauler(f, c) && !trobatObstacle) {
                        if (m_tauler[f][c].getTipus() == TIPUS_EMPTY) {
                            posicionsPossibles.push_back(Posicio(f, c));
                            f += dirsDama[d][0];
                            c += dirsDama[d][1];
                        }
                        else {
                            trobatObstacle = true;
                        }
                    }
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
    return (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES);
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
void Tauler::getCapturesDama(const Fitxa& fitxa, const Moviment& movActual, vector<Moviment>& pendents)
{
    const int dirs[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
    Posicio pos = movActual.getPosicioFinal();

    for (int d = 0; d < 4; ++d)
    {
        int df = dirs[d][0];
        int dc = dirs[d][1];
        int f = pos.getFila();
        int c = pos.getColumna();

        bool trobatEnemic = false;
        int filaEnemic = -1, colEnemic = -1;

        f += df;
        c += dc;

        while (esDinsTauler(f, c))
        {
            const Fitxa& actual = m_tauler[f][c];

            if (actual.getTipus() == TIPUS_EMPTY)
            {
                if (trobatEnemic)
                {
                    Moviment nouMov = movActual;
                    nouMov.afegeixPosicio(Posicio(f, c));
                    nouMov.setEsMovimentDeCaptura(true);
                    pendents.push_back(nouMov);

                    getCapturesDama(fitxa, nouMov, pendents);
                    break;
                }

                f += df;
                c += dc;
            }
            else if (actual.getColor() != fitxa.getColor())
            {
                if (!trobatEnemic)
                {
                    trobatEnemic = true;
                    filaEnemic = f;
                    colEnemic = c;

                    f += df;
                    c += dc;
                }
                else
                {
                    break; // ya se encontró un enemigo, no puede haber otro seguido
                }
            }
            else
            {
                break; // ficha del mismo color
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
void Tauler::getCapturesDisponibles(const Fitxa& fitxa, const Moviment& movActual, vector<Moviment>& pendents)
{
    int dirs[2][2];
    if (fitxa.getColor() == COLOR_NEGRE)
    {
        dirs[0][0] = -1; dirs[0][1] = -1; // arriba izquierda
        dirs[1][0] = -1; dirs[1][1] = 1;  // arriba derecha
    }
    else
    {
        dirs[0][0] = 1; dirs[0][1] = -1; // abajo izquierda
        dirs[1][0] = 1; dirs[1][1] = 1;  // abajo derecha
    }

    Posicio pos = movActual.getPosicioFinal();

    for (int i = 0; i < 2; ++i)
    {
        int fila1 = pos.getFila() - 1 + dirs[i][0]; // fila enemigo
        int col1 = pos.getColumna() + dirs[i][1];   // col enemigo

        int fila2 = fila1 + dirs[i][0];
        int col2 = col1 + dirs[i][1];

        if (esDinsTauler(fila1, col1) && esDinsTauler(fila2, col2))
        {
            const Fitxa& enemic = m_tauler[fila1][col1];
            const Fitxa& desti = m_tauler[fila2][col2];

            if (enemic.getTipus() != TIPUS_EMPTY && enemic.getColor() != fitxa.getColor() && desti.getTipus() == TIPUS_EMPTY)
            {
                Moviment nouMov = movActual;
                nouMov.afegeixPosicio(Posicio(fila2 + 1, col2)); // Recorda que fila comenca en 1
                nouMov.setEsMovimentDeCaptura(true);
                pendents.push_back(nouMov);

                // Buscar captures en cadena
                getCapturesDisponibles(fitxa, nouMov, pendents);
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
            // Actualizar todos los movimientos válidos del tablero
            actualitzaMovimentsValids();

            // Buscar si existe un movimiento válido para esa ficha
            const Fitxa& fitxa = m_tauler[filaOrig][colOrig];
            int indexMov = -1;

            for (int i = 0; i < fitxa.getNumMovimentsValids(); ++i)
            {
                if (fitxa.getMovimentValid(i).getPosicioFinal() == desti)
                {
                    indexMov = i;
                    break;
                }
            }

            if (indexMov == -1)
            {
                valid = false;
            }
            else
            {
                const Moviment& mov = fitxa.getMovimentValid(indexMov);

                // Verificar si existe alguna captura en TODO el tablero
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

                if (hiHaCaptura && !mov.getEsMovimentDeCaptura())
                {
                    bool laFitxaTeniaCaptura = false;
                    for (int i = 0; i < fitxaOrig.getNumMovimentsValids(); ++i)
                    {
                        if (fitxaOrig.getMovimentValid(i).getEsMovimentDeCaptura())
                        {
                            laFitxaTeniaCaptura = true;
                            break;
                        }
                    }

                    if (laFitxaTeniaCaptura)
                    {
                        m_tauler[filaOrig][colOrig] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, origen); // Bufar
                        valid = true;
                    }
                    else
                    {
                        valid = false; // No tenía captura, pero intentó mover cuando otras sí podían
                    }
                }
                else
                {
                    // Ejecutar captura (elimina las piezas comidas)
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

                    // Promocionar si ha llegado al final del tablero
                    if ((m_tauler[filaDest][colDest].getTipus() == TIPUS_NORMAL) &&
                        ((m_tauler[filaDest][colDest].getColor() == COLOR_BLANC && filaDest == 7) ||
                            (m_tauler[filaDest][colDest].getColor() == COLOR_NEGRE && filaDest == 0)))
                    {
                        m_tauler[filaDest][colDest].convertirADama();
                        calculaMovimentsFitxa(filaDest, colDest); // Recalcular movimientos de dama
                    }
                }
            }
        }
    }

    actualitzaMovimentsValids(); // Siempre actualizar al final
    return valid;
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
    if (!esDinsTauler(fila, col))
        return;

    Fitxa& fitxa = m_tauler[fila][col];
    Posicio origen(fila, col);  // Use direct matrix indices
    fitxa.resetMovimentsValids();

    vector<Moviment> pendents;
    bool hiHaCaptura = false;

    // Check for captures first (mandatory moves)
    Moviment inici(origen);
    if (fitxa.getTipus() == TIPUS_DAMA) {
        getCapturesDama(fitxa, inici, pendents);
    }
    else {
        getCapturesDisponibles(fitxa, inici, pendents);
    }

    // Add all found captures
    for (auto& m : pendents) {
        if (m.getNumPosicions() > 1) {
            m.setEsMovimentDeCaptura(true);
            fitxa.afegeixMovimentValid(m);
            hiHaCaptura = true;
        }
    }

    // If no captures, generate simple moves
    if (!hiHaCaptura) {
        if (fitxa.getTipus() == TIPUS_NORMAL) {
            int dir = (fitxa.getColor() == COLOR_BLANC) ? -1 : 1;  // White moves up (-1), black down (+1)

            // Check both diagonal directions
            for (int dc = -1; dc <= 1; dc += 2) {
                int nf = fila + dir;
                int nc = col + dc;

                if (esDinsTauler(nf, nc) && m_tauler[nf][nc].getTipus() == TIPUS_EMPTY) {
                    Moviment m(origen);
                    m.afegeixPosicio(Posicio(nf, nc));
                    fitxa.afegeixMovimentValid(m);
                }
            }
        }
        else if (fitxa.getTipus() == TIPUS_DAMA) {
            // Queen moves in all 4 diagonals
            int dirs[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

            for (int d = 0; d < 4; ++d) {
                int f = fila + dirs[d][0];
                int c = col + dirs[d][1];

                while (esDinsTauler(f, c)) {
                    if (m_tauler[f][c].getTipus() == TIPUS_EMPTY) {
                        Moviment mov(origen);
                        mov.afegeixPosicio(Posicio(f, c));
                        fitxa.afegeixMovimentValid(mov);
                    }
                    else {
                        break;  // Blocked by another piece
                    }
                    f += dirs[d][0];
                    c += dirs[d][1];
                }
            }
        }
    }
}

void Tauler::visualitza() const
{
    // Dibuixa el tauler (fons i gràfic)
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

    for (int i = 0; i < N_FILES; ++i)
    {
        for (int j = 0; j < N_COLUMNES; ++j)
        {
            m_tauler[i][j].visualitza(); // Cada fitxa dibuixa si no és buida
        }
    }
}


const Fitxa& Tauler::getFitxa(const Posicio& pos) const
{
    int fila = pos.getFila();
    int col = pos.getColumna();
    return m_tauler[fila][col];
}


bool Tauler::hiHaCapturaGlobal(ColorFitxa color)
{
    bool hiHaCapturaGlobal = false;
    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            const Fitxa& f = m_tauler[i][j];
            if (f.getTipus() != TIPUS_EMPTY && f.getColor() == color)
            {
                for (int k = 0; k < f.getNumMovimentsValids(); ++k)
                {
                    if (f.getMovimentValid(k).getEsMovimentDeCaptura())
                        hiHaCapturaGlobal = true;
                }
            }
        }
    }
    return hiHaCapturaGlobal;
}


bool Tauler::esMovimentDeCaptura(const Posicio& origen, const Posicio& desti) const
{
    bool esMovCaptura = false;
    int fila = origen.getFila() - 1;
    int col = origen.getColumna();

    if (esDinsTauler(fila, col))
    {
        const Fitxa& fitxa = m_tauler[fila][col];
        for (int i = 0; i < fitxa.getNumMovimentsValids(); ++i)
        {
            const Moviment& m = fitxa.getMovimentValid(i);
            if (m.getPosicioFinal() == desti && m.getEsMovimentDeCaptura())
            {
                esMovCaptura = true;
                break;
            }
        }
    }
    return esMovCaptura;
}


void Tauler::bufaFitxa(const Posicio& pos)
{
    int fila = pos.getFila() - 1;
    int col = pos.getColumna();

    if (esDinsTauler(fila, col))
        m_tauler[fila][col] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, pos);
}
