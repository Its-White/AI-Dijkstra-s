#pragma once
#include "Vector2.h"
#include <vector>
#include "Edge.h"
#include <list>
class Edge;

class Node
{
public:
	Node();
	~Node();

	Vector2 getNodePos();
	void setNodePos(Vector2 pos);
	void addPath(Edge newEdge);
	bool beenVisited() { return visited; };
	void setVisited(bool v);
	bool beenQueued() { return queued; };
	void setQueued(bool q);
	const std::list<Edge> & getEdges() { return edges; };

	Node* from;
	int costFromStart;
	int heuristic;


private:
	Vector2 position;
	std::list<Edge>edges;
	bool visited;
	bool queued;
};