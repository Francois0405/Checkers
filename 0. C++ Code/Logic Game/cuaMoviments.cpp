#include "CuaMoviments.h"
#include <iostream>

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