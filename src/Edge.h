#pragma once
#include <vector>
#include "Node.h"
class Node;

class Edge
{
public:
	Edge();
	Edge(Node* start, Node* dest, int newCost);
	~Edge();
	Node* getSource() const { return source; }
	Node* getDest() const { return destination; }
	int getCost() const { return cost; }

private:
	int cost;
	Node* source;
	Node* destination;
};