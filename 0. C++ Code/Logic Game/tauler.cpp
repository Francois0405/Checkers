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
            m_tauler[i][j] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, Posicio(i , j));
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
                << ") ("<< tipus << ") per la posicio : " << posicioStr << endl;
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
            // Se busca actualizar todas las piezas del juego, por lo tanto, cojemos cada fitxa.
            Fitxa& fitxa = m_tauler[i][j];
            // Setter de Posicio (atributo)
            fitxa.setPosicio(Posicio(i , j));

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

void Tauler::getPosicionsPossibles(const Posicio& origen, vector<Posicio>& posicionsPossibles)
{
    posicionsPossibles.clear(); // Limpia el vector de posiciones posibles
    int fila = origen.getFila();
    int col = origen.getColumna();

    if (esDinsTauler(fila, col))
    {
        const Fitxa& fitxa = m_tauler[fila][col]; // Obtenemos la ficha en la posición origen

        if (fitxa.getTipus() != TIPUS_EMPTY)
        {
            int dirs[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} }; // as las direcciones posibles para una dama
            for (int d = 0; d < 4; ++d)
            {
                int df = dirs[d][0]; // Delta fila
                int dc = dirs[d][1]; // Delta columna

                // Si es una ficha normal, solo se mueve adelante
                if (fitxa.getTipus() == TIPUS_NORMAL)
                {
                    int dir = (fitxa.getColor() == COLOR_BLANC) ? -1 : 1;
                    for (int dc = -1; dc <= 1; dc += 2)
                    {
                        int f = fila + dir;
                        int c = col + dc;

                        if (esDinsTauler(f, c) && m_tauler[f][c].getTipus() == TIPUS_EMPTY)
                        {
                            posicionsPossibles.push_back(Posicio(f, c));
                        }
                    }
                }
                else if (fitxa.getTipus() == TIPUS_DAMA)
                {
                    // Las damas pueden avanzar en la dirección hasta chocar con algo
                    int f = fila + df;
                    int c = col + dc;
                    bool trobatObstacle = false;

                    while (esDinsTauler(f, c) && !trobatObstacle)
                    {
                        if (m_tauler[f][c].getTipus() == TIPUS_EMPTY)
                        {
                            posicionsPossibles.push_back(Posicio(f, c));
                        }
                        else
                        {
                            // Si encontramos una ficha, no podemos seguir avanzando en esta dirección
                            trobatObstacle = true;
                        }
                        f += df;
                        c += dc;
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

        while (esDinsTauler(f - 1, c))
        {
            const Fitxa& actual = m_tauler[f - 1][c];

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
                    filaEnemic = f - 1;
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
        dirs[0][0] = 1; dirs[0][1] = -1;  // Negro: captura hacia abajo
        dirs[1][0] = 1; dirs[1][1] = 1;
    }
    else
    {
        dirs[0][0] = -1; dirs[0][1] = -1; // Blanco: captura hacia arriba
        dirs[1][0] = -1; dirs[1][1] = 1;
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
                nouMov.afegeixPosicio(Posicio(fila2, col2)); // Recorda que fila comenca en 1
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
    int filaOrig = origen.getFila();
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

                            m_tauler[filaCap][colCap] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, Posicio(filaCap, colCap));
                        }
                    }

                    // Mover la ficha
                    int filaDest = desti.getFila();
                    int colDest = desti.getColumna();

                    m_tauler[filaDest][colDest] = fitxaOrig;
                    m_tauler[filaDest][colDest].setPosicio(desti);
                    m_tauler[filaOrig][colOrig] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, origen);

                    // Promocionar si ha llegado al final del tablero
                    if ((m_tauler[filaDest][colDest].getTipus() == TIPUS_NORMAL) &&
                        ((m_tauler[filaDest][colDest].getColor() == COLOR_BLANC && filaDest == 0) || // Blanco llega a fila 0 (arriba)
                            (m_tauler[filaDest][colDest].getColor() == COLOR_NEGRE && filaDest == 7)))   // Negro llega a fila 7 (abajo)
                    {
                        m_tauler[filaDest][colDest].convertirADama();
                        calculaMovimentsFitxa(filaDest, colDest);
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
    Posicio origen = fitxa.getPosicio();
    fitxa.resetMovimentsValids();

    vector<Moviment> pendents;
    bool hiHaCaptura = false;

    // Inicializamos las capturas desde la posición inicial
    Moviment inici(origen);
    if (fitxa.getTipus() == TIPUS_DAMA)
        getCapturesDama(fitxa, inici, pendents);
    else
        getCapturesDisponibles(fitxa, inici, pendents);

    // Añadimos todas las capturas encontradas
    for (auto& m : pendents)
    {
        if (m.getNumPosicions() > 1)
        {
            m.setEsMovimentDeCaptura(true);
            fitxa.afegeixMovimentValid(m);
            hiHaCaptura = true;
        }
    }

    // Si no hay capturas, generamos movimientos simples
    if (!hiHaCaptura)
    {
        if (fitxa.getTipus() == TIPUS_NORMAL)
        {
            int dir = (fitxa.getColor() == COLOR_BLANC) ? -1 : 1;
            for (int dc = -1; dc <= 1; dc += 2)
            {
                int nf = fila + dir;
                int nc = col + dc;
                if (esDinsTauler(nf, nc) && m_tauler[nf][nc].getTipus() == TIPUS_EMPTY)
                {
                    Moviment m(origen);
                    m.afegeixPosicio(Posicio(nf, nc));
                    fitxa.afegeixMovimentValid(m);
                }
            }
        }
        else if (fitxa.getTipus() == TIPUS_DAMA)
        {
            int dirs[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
            for (int d = 0; d < 4; ++d)
            {
                int f = fila + dirs[d][0];
                int c = col + dirs[d][1];

                while (esDinsTauler(f, c) && m_tauler[f][c].getTipus() == TIPUS_EMPTY)
                {
                    Moviment mov(origen);
                    mov.afegeixPosicio(Posicio(f, c));
                    fitxa.afegeixMovimentValid(mov);
                    f += dirs[d][0];
                    c += dirs[d][1];
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


void Tauler::visualitza() const
{
    // Dibuixa el tauler (fons i gràfic)
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

    cout << "[DEBUG] Board View:" << endl;
    for (int i = 0; i < N_FILES; ++i)
    {
        for (int j = 0; j < N_COLUMNES; ++j)
        {
            m_tauler[i][j].visualitza(); // Cada fitxa dibuixa si no és buida
            cout << "[" << m_tauler[i][j].getLletra() << "]";
        }
        cout << endl;
    }
}



const Fitxa& Tauler::getFitxa(const Posicio& pos) const
{
    int fila = pos.getFila() - 1;
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
    int fila = pos.getFila();
    int col = pos.getColumna();

    if (esDinsTauler(fila, col))
        m_tauler[fila][col] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, pos);
}
