#pragma once
#include <vector>
#include "Node.h"
#include <list>
#include <string>
#include <vector>
#include <queue>
class Graph
{
public:
	Graph();
	~Graph();

	void addNode(Vector2 pos);
	void connectNodes(Node* a, Node* b, float m_cost);
	std::vector<Node*>* reachable(std::string name);
	std::vector<Node*>* shortestPath(std::string nameStart, std::string nameFinish);

private:
	std::vector<Node> nodes;
	Vector2 NodePos;

	bool visited;
	bool unvisited;
};