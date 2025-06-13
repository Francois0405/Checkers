#ifndef JOC_H
#define JOC_H

#include <stdio.h>
#include <queue>
#include "info_joc.hpp"
#include "tauler.hpp"
#include "cuaMoviments.h"

using namespace std;

class Joc
{
public:
    ModeJoc menu();
    void mouMaquina();
    void inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments);
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus, ModeJoc mode);
    void finalitza(const string& nomFitxer, ModeJoc mode);
    ColorFitxa getTornActual() const { return m_tornActual; }
    bool comprovaFinalPartida();


private:
    Tauler m_tauler;
    bool m_fitxaSeleccionada = false;
    int m_filaSeleccionada = -1;
    int m_colSeleccionada = -1;
    ColorFitxa m_tornActual = COLOR_BLANC;
    string m_guanyador = "";
    bool m_partidaAcabada = false;
	CuaMoviment m_cuaMoviments;
};

struct MovimentPossible {
    Posicio origen;
    Moviment moviment;
};


#endif 
