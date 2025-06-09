#ifndef JOC_H
#define JOC_H

#include <stdio.h>
#include <queue>
#include "info_joc.hpp"
#include "tauler.hpp"

using namespace std;

class Joc
{
public:
    void inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments);
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    void finalitza();
private:
    Tauler m_tauler;
};

#endif 
