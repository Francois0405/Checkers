#include "CuaMoviments.h"

CuaMoviment::~CuaMoviment() 
{
	if (!empty)
	{
		while ()
		{

		}
	}
}

void CuaMoviment::push(Moviment m)
{
	if (!empty)
	{

		
		m_size++;
	}
}

void CuaMoviment::pop()
{

	m_size--;
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