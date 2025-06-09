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
	void push(const Moviment m); // Add a movement to the queue
	void pop(); // Remove the front movement from the queue

	Moviment getMovFront(); // Get the front movement without removing it
	Moviment getMovBack(); // get the back movement

	// Getters and Setters for front and back nodes
	NodeMoviment* getFront() { return m_front; }
	NodeMoviment* getBack() { return m_back; }
	void setFront(NodeMoviment* front) { m_front = front; }
	void setBack(NodeMoviment* back) { m_back = back; }
	int getSize() {	return m_size;} // Get the number of movements in the queue
	
	bool empty(); // Check if the queue is empty
private:
	NodeMoviment* m_front; // Front of the queue
	NodeMoviment* m_back;  // Rear of the queue
	int m_size; // size of the queue
};

#endif