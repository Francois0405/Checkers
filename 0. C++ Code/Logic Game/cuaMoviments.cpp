#include "CuaMoviments.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

CuaMoviment::~CuaMoviment() 
{
	while (!empty())
	{
		pop();
	}
	m_front = nullptr;
	m_back = nullptr;
	m_size = 0;
	cout << "[DEBUG] ~CuaMoviment()" << endl;

}

void CuaMoviment::push(Moviment moviment)
{
	NodeMoviment* nouNode = new NodeMoviment(moviment);

	if (empty()) { //si la cua esta buida, nouNode es el primer i el ultim
		m_front = nouNode;
		m_back = nouNode;
		cout << "[DEBUG] push() correcte a empty" << endl;
	}
	else { //si no esta buida, ho afegim al final de la cua
		m_back->setNext(nouNode); 
		m_back = nouNode;
		cout << "[DEBUG] push() correcte a existent" << endl;
	}
	m_size++;
}

void CuaMoviment::pop()
{
	if (!empty())
	{
		NodeMoviment* nodeAEliminar = m_front;
		m_front = m_front->getNext(); //avancem el node al davant
		delete nodeAEliminar; //alliberem node

		if (m_front == nullptr)
		{
			m_back = nullptr;
		}
		cout << "[DEBUG] pop() correcte" << endl;
		m_size--;
	}
	else
		cerr << "[ERROR] pop():		LLISTA BUIDA" << endl;
}

Moviment CuaMoviment::getMovFront()
{
	if (!empty())
		return m_front->getMoviment();
	else
		cerr << "[ERROR] getMovFront():	LLISTA BUIDA";
		throw runtime_error("ERROR: getMovFront(), llista buida");
}

Moviment CuaMoviment::getMovBack()
{
	if (!empty())
		return m_back->getMoviment();
	else
		cerr << "[ERROR] getMovBack():	LLISTA BUIDA";
		throw runtime_error("ERROR: getMovBack(), llista buida");
}

bool CuaMoviment::empty()
{
	return (m_front == nullptr || m_back == nullptr);
}

void CuaMoviment::print()
{
	if (empty())
	{
		cout << "[DEBUG] printCuaMoviments(): Cua buida" << endl;
		return;
	}
	NodeMoviment* nodeActual = m_front;
	while (nodeActual != nullptr)
	{
		cout << nodeActual->getMoviment() << endl;
		nodeActual = nodeActual->getNext();
	}
	cout << "[DEBUG] printCuaMoviments(): Cua impresa correctament" << endl;
}

void CuaMoviment::storeCua(const string& nomFitxer) 
{
	ofstream fitxer(nomFitxer);
	if (!fitxer.is_open()) {
		cerr << "[ERROR] storeCua(): No s'ha pogut obrir el fitxer " << nomFitxer << endl;
		return;
	}

	if (m_front == nullptr) {
		cout << "[WARNING] storeCua(): Cua buida, no s'ha guardat res" << endl;
		fitxer.close();
		return;
	}

	NodeMoviment* nodeActual = m_front;
	while (nodeActual != nullptr) {
		const Moviment& mov = nodeActual->getMoviment();
		if (mov.getNumPosicions() >= 2) {  // Ensure valid move
			fitxer << mov.getPosicioInicial() << " "
				<< mov.getPosicioFinal() << endl;
		}
		nodeActual = nodeActual->getNext();
	}
	fitxer.close();
	cout << "[DEBUG] storeCua(): " << m_size << " moviments emmagatzemats a "
		<< nomFitxer << endl;
}


void CuaMoviment::loadCua(const string& nomFitxer)
{
	ifstream fitxer(nomFitxer);
	if (!fitxer.is_open()) {
		cerr << "[ERROR] loadCua(): No s'ha pogut obrir el fitxer " << nomFitxer << endl;
		return;
	}

	string line;
	while (getline(fitxer, line)) {
		// Skip empty lines
		if (line.empty()) continue;

		istringstream iss(line);
		Moviment moviment;
		if (iss >> moviment) {  // Only push if successfully read
			push(moviment);
		}
		else {
			cerr << "[WARNING] loadCua(): Linea mal formada: " << line << endl;
		}
	}

	fitxer.close();
	cout << "[DEBUG] loadCua(): " << m_size << " moviments carregats des de "
		<< nomFitxer << endl;
}