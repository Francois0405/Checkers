//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./joc.hpp"
#include "./info_joc.hpp"


int main(int argc, const char* argv[])
{
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(TAMANY_PANTALLA_X, TAMANY_PANTALLA_Y);
    //Mostrem la finestra grafica
    pantalla.show();

    string nomFitxerMoviments = "N/A";
    Joc joc;
    ModeJoc mode = joc.menu(nomFitxerMoviments);

    string modeString;
    switch (mode)
    {
    case 0:
        modeString = "NORMAL";
        break;
    case 1:
        modeString = "REPLAY";
        break;
    case 2:
        modeString = "ORDINADOR";
        break;
    case 3:
        modeString = "NONE";
        break;
    default:
        throw runtime_error("[ERROR] UNKNOWN MODE");
        break;
    }

    cout << "[DEBUG] MODE: " << modeString << endl;
    cout << "[DEBUG] FitxerMov: " << nomFitxerMoviments << endl;
    // PAS 1. INICIALITZEM EL JOC
    joc.inicialitza(mode, "..\\taulerInicial.txt", nomFitxerMoviments);
    bool final = false;

    do
    {
        // Captura tots els events de ratolí i teclat de l'ultim cicle
        pantalla.processEvents();

        bool mouseStatus = Mouse_getBtnLeft();
        int mousePosX = Mouse_getX();
        int mousePosY = Mouse_getY();
        
        // PAS 2. ACTUALITZEM SI NO S'HA ACABAT I RETORNA EL BOOL (GUANYAT)
        final = joc.actualitza(mousePosX, mousePosY, mouseStatus);

        // Actualitza la pantalla
        pantalla.update();
    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && !final);
        // Sortim del bucle si pressionem ESC o quan s'acaba

    if (final)
    {
        // PAS 3. FINALITZEM EL JOC
        joc.finalitza();
        cout << "[DEBUG] JOC FINALITZAT" << endl;
    }
    else
        cout << "[DEBUG] ESC pressionat" << endl;
    system("pause");
    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();
    return 0;
}

