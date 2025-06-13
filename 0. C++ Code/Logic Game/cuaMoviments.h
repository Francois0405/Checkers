#pragma once

#ifndef CUAMOVIMENTS_H
#define CUAMOVIMENTS_H

#include "moviment.h"
#include "node_moviment.h"

using namespace std;

class CuaMoviment
{
public:
	CuaMoviment() : m_front(nullptr), m_back(nullptr), m_size(0) {} // Constructor
	~CuaMoviment(); // Destructor
	void push(const Moviment moviment); // afegeix moviment a la cua 
	void pop(); // elimina el primer element de la cua 

	Moviment getMovFront(); // retorna front moviments sebse eliminarlos
	Moviment getMovBack(); // retonra back moviments

	// Getters and Setters dels nodes front i back
	NodeMoviment* getFront() { return m_front; }
	NodeMoviment* getBack() { return m_back; }
	void setFront(NodeMoviment* front) { m_front = front; }
	void setBack(NodeMoviment* back) { m_back = back; }
	int getSize() {	return m_size;} // retorna num de moviments en la cua 
	
	bool empty(); // crompova si esta empty
	void print(); // imprimeix la cua de moviments
private:
	NodeMoviment* m_front; // Front cua
	NodeMoviment* m_back;  // Rear cua
	int m_size; // mida cua
};

#endif