#include "Edge.h"

Edge::Edge() 
{
}

Edge::Edge(Node * start, Node * dest, int newCost)
{
	source = start;
	destination = dest;
	cost = newCost;
}

Edge::~Edge() 
{
}