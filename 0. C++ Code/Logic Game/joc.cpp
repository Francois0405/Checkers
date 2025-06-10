//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "joc.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "GraphicManager.h"


void Joc::inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments)
{
	if (mode == MODE_JOC_NORMAL)
	{
		// El fitxer indicat al paràmetre nomFitxerMoviments s’haurà d’utilitzar
		// per guardar, al final de la partida, tots els moviments que s’hagin fet
		// durant el desenvolupament de la partida

		m_tauler.inicialitza(nomFitxerTauler);
		m_tauler.actualitzaMovimentsValids();

	}
	else if (mode == MODE_JOC_REPLAY)
	{
		// S’haurà d’inicialitzar la cua de moviments a reproduir amb la 
		// informació del fitxer indicat al paràmetre nomFitxerMoviments
			
		nomFitxerMoviments;
	}
}

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{
	//TODO 1: Interactuar amb la crida per dibuixar gràfics (sprites). =DONE
	// 	      Dibuixar a pantalla el fons i el gràfic amb el tauler buit. =DONE
	//------------------------------------------------------------------

	//TODO 1.1 Afegir l'include de GraphicManager --> #include "GraphicManager.h" =DONE
	//TODO 1.2 Fer la crida de dibuixar un sprite --> GraphicManager::getInstance()->drawSprite(image, posX, posY); =DONE
	//	    Per començar podem cridar el drawSprite amb els params --> 
	//          (GRAFIC_FONS,0,0) i 
	//          (GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER)

	// Important Primer mostrar el fons sino el fons tapara tauler.
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);
	m_tauler.visualitza();

	//TODO 1.3: Dibuixar a pantalla el gràfic amb el tauler i una fitxa blanca a la posició (fila, columna ) del tauler =DONE

	/*
	m_columna = ((POS_X_TAULER + CASELLA_INICIAL_X)) / AMPLADA_CASELLA;
	m_fila = ((POS_Y_TAULER + CASELLA_INICIAL_Y)) / ALCADA_CASELLA;

	int posX1 = POS_X_TAULER + CASELLA_INICIAL_X + (m_columna * AMPLADA_CASELLA);
	int posY1 = POS_Y_TAULER + CASELLA_INICIAL_Y + (m_fila * ALCADA_CASELLA);
	GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, posX1, posY1);
	*/

	//TODO 2: Interactuar amb el ratolí.
	//------------------------------------------------------------------
	//TODO 2.1: Dibuixar la fitxa blanca al tauler només si estem pressionant el botó del ratolí
	/*if (mouseStatus && (mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X)) &&
		(mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y) &&
		(mousePosX <= (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER)) &&
		(mousePosY <= (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER)))
	{
		m_columna = (mousePosX - (POS_X_TAULER + CASELLA_INICIAL_X)) / AMPLADA_CASELLA;
		m_fila = (mousePosY - (POS_Y_TAULER + CASELLA_INICIAL_Y)) / ALCADA_CASELLA;
	}
	int posX = POS_X_TAULER + CASELLA_INICIAL_X + (m_columna * AMPLADA_CASELLA);
	int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + (m_fila * ALCADA_CASELLA);
	GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, posX, posY);*/

	int posTextX = POS_X_TAULER;
	int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 130;
	string title = "Mouse Cursor";
	string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
	string title2 = "Checkers";
	//string msg2 = "PosX: " + to_string(posX) + ", PosY: " + to_string(posY);
	GraphicManager::getInstance()->drawFont(FONT_GREEN_30, posTextX, posTextY - 20, 0.8, title);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, msg);
	GraphicManager::getInstance()->drawFont(FONT_GREEN_30, posTextX, posTextY + 25, 0.8, title2);
	//GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 50, 0.8, msg2);


	//TODO 2.2: Dibuixar la fitxa blanca al tauler només si estem pressionant el botó del ratolí i el ratolí
	// està dins del límits del tauler
	bool dinsTauler = mousePosX >= POS_X_TAULER + CASELLA_INICIAL_X &&
		mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y &&
		mousePosX < POS_X_TAULER + CASELLA_INICIAL_X + NUM_COLS_TAULER * AMPLADA_CASELLA &&
		mousePosY < POS_Y_TAULER + CASELLA_INICIAL_Y + NUM_FILES_TAULER * ALCADA_CASELLA;

	if (mouseStatus && dinsTauler)
	{
		int col = (mousePosX - (POS_X_TAULER + CASELLA_INICIAL_X)) / AMPLADA_CASELLA;
		int fila = (mousePosY - (POS_Y_TAULER + CASELLA_INICIAL_Y)) / ALCADA_CASELLA;

		Posicio posicioClicada(fila + 1, col);

		const Fitxa& fitxaClicada = m_tauler.getFitxa(posicioClicada);

		if (fitxaClicada.getTipus() != TIPUS_EMPTY && fitxaClicada.getColor() == m_tornActual)
		{
			m_filaSeleccionada = fila;
			m_colSeleccionada = col;
			m_fitxaSeleccionada = true;
		}
	

		else if (m_fitxaSeleccionada)
		{
			Posicio origen(m_filaSeleccionada + 1, m_colSeleccionada);
			Posicio desti(fila + 1, col);

			if (m_tauler.mouFitxa(origen, desti))
			{
				m_fitxaSeleccionada = false;
				m_tauler.actualitzaMovimentsValids();
				if (m_tornActual == COLOR_BLANC)
					m_tornActual = COLOR_NEGRE;
				else
					m_tornActual = COLOR_BLANC;
			}
		}
	}



	//TODO 2.3: Dibuixar la fitxa blanca al tauler només si estem pressionant el botó del ratolí i el ratolí
	// està dins del límits del tauler. Dibuixa la fitxa a la casella on està el ratolí

	if (m_fitxaSeleccionada)
	{
		Posicio posActual(m_filaSeleccionada + 1, m_colSeleccionada);
		const Fitxa& fitxa = m_tauler.getFitxa(posActual);

		// Si la ficha ya no existe (ha sido comida), cancelar selección
		if (fitxa.getTipus() == TIPUS_EMPTY)
		{
			m_fitxaSeleccionada = false;
		}
		else
		{
			int posX = POS_X_TAULER + CASELLA_INICIAL_X + m_colSeleccionada * AMPLADA_CASELLA;
			int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + m_filaSeleccionada * ALCADA_CASELLA;

			if (fitxa.getColor() == COLOR_NEGRE)
			{
				if (fitxa.getTipus() == TIPUS_DAMA)
					GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_NEGRA, posX, posY);
				else
					GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_NEGRA, posX, posY);
			}
			else if (fitxa.getColor() == COLOR_BLANC)
			{
				if (fitxa.getTipus() == TIPUS_DAMA)
					GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_BLANCA, posX, posY);
				else
					GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, posX, posY);
			}

			// Mostrar moviments valids
			for (int i = 0; i < fitxa.getNumMovimentsValids(); ++i)
			{
				Posicio desti = fitxa.getMovimentValid(i).getPosicioFinal();
				int x = POS_X_TAULER + CASELLA_INICIAL_X + desti.getColumna() * AMPLADA_CASELLA;
				int y = POS_Y_TAULER + CASELLA_INICIAL_Y + (desti.getFila() - 1) * ALCADA_CASELLA;
				GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, x, y);
			}
		}
	}

	//TODO 2.4: Dibuixar la fitxa blanca a la casella on cliquem al ratolí. La fitxa s'ha de mantenir dibuixada
	// a la casella quan deixem de clicar amb el ratolí. Quan cliquem a una altra casella, la fitxa canvia de posició
	// a la nova casella



	// TODO 3: Imprimir text per pantalla
	//------------------------------------------
	// TODO 3.1: Mostrar la posició actual del ratolí a sota del tauler



	return false;
}

void Joc::finalitza()
{

}
