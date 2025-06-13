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
#include <thread>
#include <chrono>


ModeJoc Joc::menu(string& nomFitxerMoviments)
{
	cout << "    ___             ______      ______                          " << endl
		<< "   |_  |            |  _  \\     |  _  \\                         " << endl
		<< "     | | ___   ___  | | | |___  | | | |__ _ _ __ ___   ___  ___ " << endl
		<< "     | |/ _ \\ / __| | | | / _ \\ | | | / _` | '_ ` _ \\ / _ \\/ __|" << endl
		<< "/ \\__/ / (_) | (__  | |/ /  __/ | |/ / (_| | | | | | |  __/\\__ \\ " << endl
		<< " \\____/ \\___/ \\___| |___/ \\___| |___/ \\__,_|_| |_| |_|\\___||___/" << endl << endl;

	cout << endl << "==============================================================" << endl << endl;
	cout << "1. Jugar contra un adversari" << endl
		<< "2. Visualitzar una partida (Replay)" << endl
		<< "3. Jugar contra un ordinador" << endl;
	cout << endl << "Trieu una opcio: ";
	int opcio;
	cin >> opcio;
	ModeJoc mode;
	switch (opcio)
	{
	case 1:
		mode = MODE_JOC_NORMAL;
		break;
	case 2: 
		mode = MODE_JOC_REPLAY;
		break;
	case 3:
		mode = MODE_JOC_ORDINADOR;
		break;
	default:
		mode = MODE_JOC_NONE;
		throw runtime_error("[ERROR] MODE JOC NO VALID");
		break;
	}
	while (opcio > 5 || opcio < 1)
	{
		cout << "ERROR: Trieu una opcio valida: ";
		cin >> opcio;
	}
	system("CLS");
	if (mode == MODE_JOC_NORMAL || mode == MODE_JOC_ORDINADOR)
	{
		cout << "=== COM JUGAR A LES DAMES ===" << endl << endl;
		cout << "1. TORNS:" << endl;
		cout << "   - Blanques (O) comencen, despres negres (X)." << endl << endl;

		cout << "2. MOVIMENTS:" << endl;
		cout << "   - Fitxes normals: Diagonal endavant." << endl;
		cout << "   - Dames (D/R): Qualsevol diagonal pot saltar varies caselles." << endl;
		cout << "   - Caselles verdes: Moviments possibles." << endl << endl;

		cout << "3. CAPTURES OBLIGATORIES:" << endl;
		cout << "   - Has de menjar si pots, sino se't bufa la fitxa (eliminacio)." << endl;
		cout << "   - Tria la captura que mengi MES fitxes." << endl << endl;

		cout << "4. DAMES:" << endl;
		cout << "   - Arriba al final del tauler per convertir-te en dama." << endl << endl;

		cout << "5. VICTORIA:" << endl;
		cout << "   - Menja totes les fitxes rivals o bloqueja-les." << endl << endl;

		cout << "CONTROLS:" << endl;
		cout << "   - [CLIC]: Selecciona i mou." << endl;
		cout << "   - [ESC]: Surt del joc." << endl << endl;

		cout << "Que comenci el joc!" << endl;
		system("pause");
		system("CLS");
	}
	else if (mode == MODE_JOC_REPLAY)
	{
		cout << "=== MODO REPLAY DE DAMES ===" << endl << endl;
		cout << "Aquest mode reprodueix una partida guardada anteriorment." << endl;
		cout << "Cada clic avancara un moviment de la partida." << endl << endl;

		cout << "COM FUNCIONA:" << endl;
		cout << "1. CARREGA LA PARTIDA:" << endl;
		cout << "   - Introdueix el nom o ruta de l'arxiu guardat." << endl;
		cout << "   - El sistema llegira els moviments i els mostrara pas a pas." << endl << endl;

		cout << "2. REPRODUCCIO:" << endl;
		cout << "   - Fes clic per veure cada moviment consecutiu." << endl;
		cout << "   - Les fitxes es mouran automaticament segons la partida original." << endl;

		cout << "3. CONTROLS:" << endl;
		cout << "   - [CLIC]: Avancar al seguent moviment." << endl;
		cout << "   - [ESC]: Sortir del mode replay." << endl << endl;

		cout << "Introdueix el nom o ruta de l'arxiu que vols reproduir:" << endl;
		cout << "> ";
		cin >> nomFitxerMoviments;
		system("pause");
		system("CLS");
	}

	return mode;
}

void Joc::inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments)
{
	if (mode == MODE_JOC_NORMAL || mode == MODE_JOC_ORDINADOR)
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


void Joc::mouMaquina()
{
	//la linia serveix per poder tenir temps a veure el moviment de la maquina
	this_thread::sleep_for(std::chrono::milliseconds(2000));


	ColorFitxa colorMaquina = COLOR_BLANC; // La máquina juega como blancas

	m_tauler.actualitzaMovimentsValids();

	std::vector<MovimentPossible> movimentsPossibles;

	// Recorremos el tablero buscando movimientos de fichas blancas
	for (int i = 0; i < N_FILES; ++i) {
		for (int j = 0; j < N_COLUMNES; ++j) {
			Posicio pos(i + 1, j);
			const Fitxa& fitxa = m_tauler.getFitxa(pos);

			if (fitxa.getTipus() != TIPUS_EMPTY && fitxa.getColor() == colorMaquina) {
				for (int k = 0; k < fitxa.getNumMovimentsValids(); ++k) {
					MovimentPossible mp;
					mp.origen = pos;
					mp.moviment = fitxa.getMovimentValid(k);
					movimentsPossibles.push_back(mp);
				}
			}
		}
	}

	// Intentamos realizar una captura si hay alguna
	bool movimentFet = false;
	for (int i = 0; i < static_cast<int>(movimentsPossibles.size()); ++i) {
		if (movimentsPossibles[i].moviment.getEsMovimentDeCaptura()) {
			m_tauler.mouFitxa(movimentsPossibles[i].origen, movimentsPossibles[i].moviment.getPosicioFinal());
			movimentFet = true;
			break;
		}
	}
	
	// Si no ha habido captura, hacemos el primer movimiento disponible
	if (!movimentFet && !movimentsPossibles.empty()) {
		const MovimentPossible& m = movimentsPossibles[0];
		m_tauler.mouFitxa(m.origen, m.moviment.getPosicioFinal());
	}

	// Cambiar el turno al jugador
	m_tornActual = COLOR_NEGRE;
}


bool Joc::comprovaFinalPartida()
{
	bool blancPotJugar = m_tauler.jugadorPotJugar(COLOR_BLANC);
	bool negrePotJugar = m_tauler.jugadorPotJugar(COLOR_NEGRE);

	int blancVives = m_tauler.comptaFitxes(COLOR_BLANC);
	int negreVives = m_tauler.comptaFitxes(COLOR_NEGRE);

	string guanyador = "";

	if (!blancPotJugar || blancVives == 0)
		guanyador = "NEGRE";
	else if (!negrePotJugar || negreVives == 0)
		guanyador = "BLANC";

	if (!guanyador.empty())
	{
		cout << "GUANYADOR: " << guanyador << endl;
		m_partidaAcabada = true;
	}

	return m_partidaAcabada;
}


bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{
	// Important Primer mostrar el fons sino el fons tapara tauler.
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);
	m_tauler.visualitza();

	if (m_partidaAcabada)
	{
		GraphicManager::getInstance()->drawFont(FONT_GREEN_30, POS_X_TAULER + 50, POS_Y_TAULER + 500, 1.2, "PARTIDA FINALITZADA");
		return true;  // Devuelve true para indicar que ya no hay que seguir
	}

	// Implementat indicador posMouse
	int posTextX = POS_X_TAULER;
	int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 130;
	string title = "Mouse Cursor";
	string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
	GraphicManager::getInstance()->drawFont(FONT_GREEN_30, posTextX, posTextY - 20, 0.8, title);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 5, 0.8, msg);

	// Implementat indicador torn
	string torn;
	if (m_tornActual == COLOR_BLANC)
		torn = "Torn: BLANQUES";
	else
		torn = "Torn: NEGRES";
	GraphicManager::getInstance()->drawFont(FONT_GREEN_30, posTextX, posTextY + 40, 0.8, torn);


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

			bool hiHaCaptura = m_tauler.hiHaCapturaGlobal(m_tornActual);

			bool esCaptura = m_tauler.esMovimentDeCaptura(origen, desti);

			if (m_tauler.mouFitxa(origen, desti))
			{
				if (hiHaCaptura && !esCaptura)
					m_tauler.bufaFitxa(origen);  // BUFAR si debías capturar y no lo hiciste

				m_fitxaSeleccionada = false;
				m_tauler.actualitzaMovimentsValids();

				// Cambiar turno
				if (m_tornActual == COLOR_BLANC)
					m_tornActual = COLOR_NEGRE;
				else
					m_tornActual = COLOR_BLANC;

				comprovaFinalPartida();

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
	return false;
}


void Joc::finalitza()
{

}
