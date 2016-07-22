#include "Node.h"

Node::Node()
{
	costFromStart = 0;
	heuristic = 0;
	from = nullptr;
}

Node::~Node()
{
}

Vector2 Node::getNodePos()
{
	return position;
}

void Node::setNodePos(Vector2 pos)
{
	position = pos;
}

void Node::addPath(Edge newEdge)
{
	edges.push_back(newEdge);
}

void Node::setVisited(bool v)
{
	visited = v;
}

void Node::setQueued(bool q)
{
	queued = q;
}
