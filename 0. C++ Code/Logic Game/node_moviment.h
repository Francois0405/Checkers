#pragma once
#ifndef NODE_MOVIMENT_H
#define NODE_MOVIMENT_H

#include "moviment.h"

class NodeMoviment
{
public:
	Moviment getMoviment() const { return m_moviment; };
	NodeMoviment* getNext() const { return m_next; };
	void setNext(NodeMoviment* next) { m_next = next; };
	void setMoviment(const Moviment& moviment) { m_moviment = moviment; };

	NodeMoviment(): m_moviment(), m_next(nullptr) {}
	NodeMoviment(const Moviment& moviment) : m_moviment(moviment), m_next(nullptr) {}
	~NodeMoviment() {}
private:
	Moviment m_moviment;
	NodeMoviment* m_next;
};

#endif // !NODE_MOVIMENT_H
