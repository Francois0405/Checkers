#include "CuaMoviments.h"

CuaMoviment::~CuaMoviment() 
{
	while (!empty())
	{
		pop();
	}
	m_front = nullptr;
	m_back = nullptr;
	m_size = 0;
}

void CuaMoviment::push(Moviment moviment)
{
	NodeMoviment* nouNode = new NodeMoviment(moviment);

	if (empty()) { //si la cua esta buida, nouNode es el primer i el ultim
		m_front = nouNode;
		m_back = nouNode;
	}
	else { //si no esta buida, ho afegim al final de la cua
		m_back->setNext(nouNode); 
		m_back = nouNode;
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

		m_size--;
	}
}

Moviment CuaMoviment::getMovFront()
{
	return m_front->getMoviment();
}

Moviment CuaMoviment::getMovBack()
{
	return m_back->getMoviment();
}

bool CuaMoviment::empty()
{
	return (m_front == nullptr || m_back == nullptr);
}