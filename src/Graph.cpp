#include "Graph.h"
#include <cmath>
#include <math.h>


Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::addNode(Vector2 pos)
{
	Node newNode;
	newNode.setNodePos(pos);
	nodes.push_back(newNode);
}

void Graph::connectNodes(Node* a, Node* b, float m_cost)
{
	a = new Node;
	b = new Node;
}

std::vector<Node*>* Graph::reachable(std::string name)
{
	for (auto &node : nodes) 
	{
		node.setVisited(false);
		node.setQueued(false);
	}
	Node* startNode;
	std::queue<Node*> bfsQueue;
	bfsQueue.push(startNode);
	startNode->setQueued(true);

	while (!bfsQueue.empty()) 
	{
		Node* current = bfsQueue.front();
		bfsQueue.pop();
		current->setVisited(true);
		for (auto &Edge : current->getEdges()) 
		{
			if (!Edge.getDest()->beenQueued()) 
			{
				bfsQueue.push(Edge.getDest());
			}
		}
	}
	std::vector<Node*>* reachableNodes = new std::vector<Node*>;
	for (auto node : nodes) 
	{
		if (node.beenVisited()) 
		{
			reachableNodes->push_back(&node);
		}
	}
	return reachableNodes;
}

std::vector<Node*>* Graph::shortestPath(std::string nameStart, std::string nameFinish)
{
	for (Node &n : nodes) 
	{
		n.setVisited(false);
		n.costFromStart = 0;
		n.from = nullptr;
	}

	std::vector<Node*>* result = new std::vector<Node*>();

	std::vector<Node*> explored;
	std::list<Node*> connectedQueue;

	
}

