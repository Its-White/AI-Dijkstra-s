#include "Dijkstra.h"
#include <iostream>


Path::Path()
{

}

Path::Path(Node * start, Node * dest, int newCost)
{
	source = start;
	destination = dest;
	cost = newCost;
}

Path::~Path()
{
}



Node::Node()
{
}

Node::Node(std::string newName, Vector2 pos)
{
	name = newName;
	position = pos;
	costFromStart = 0.0;
	heuristic = 0.0;
	from = nullptr;
}

Node::~Node()
{
}

void Node::addPath(Path newPath)
{
	paths.push_back(newPath);
}

void Node::setVisited(bool v)
{
	visited = v;
}

void Node::setQueued(bool q)
{
	queued = q;
}


coord::coord(int inx, int iny)
{
	x = inx;
	y = iny;
}


bool nearer(Node* a, Node*b) {
	return a->costFromStart < b->costFromStart;
}

Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::addNode(std::string name, Vector2 pos)
{
	Node newNode(name, pos);
	nodes.push_back(newNode);
}

void Graph::loadNodeImage(std::string n_name, std::string fileName)
{
	Node temp;
	if (temp.getName() == n_name) 
	{
		spriteFile = fileName;
		m_sprite = new Texture(spriteFile.c_str());
	}
}

void Graph::addPath(std::string source, std::string destination, int cost)
{
	Node * sourceNode = findNode(source);
	Node * destNode = findNode(destination);
	Path newPath(sourceNode, destNode, cost);
	sourceNode->addPath(newPath);
}

Vector2 Graph::getCost(std::string firstNode, std::string finalNode)
{
	Vector2 cost;
	cost = findNode(firstNode)->getPosition() - findNode(finalNode)->getPosition();
	return cost;
}

Vector2 Graph::getNodeLocation(std::string n_name) // pass in the name of the node you want to find the location of
{
	for (auto &node : nodes)
	{
		if (node.getName() == n_name)
		{
			//std::cout << node.getPosition().x << ", " << node.getPosition().y << std::endl;
			return node.getPosition();
		}
	}
}

Node * Graph::findNode(std::string n_name)
{
	for (auto &node : nodes)
	{
		if (node.getName() == n_name)
		{
			Node * nodePtr = &node;
			return nodePtr;
		}
	}
	return nullptr; //didn't find the node with the desired name
}

Node * Graph::findScreenNode(coord m_map)
{
	int bestDist = 10000;
	Node * nodePtr = nullptr;
	// loop through the nodes and find the one that matches the location within 200 pixels
	for (auto &node : nodes)
	{
		coord map = node.getPositionOnMap();
		int diffX = map.x - m_map.x;
		int diffY = map.y - m_map.y;
		int dist = (int)sqrt(diffX*diffX + diffY*diffY);

		if (dist > 200) continue;

		if (dist < bestDist) {
			bestDist = dist;
			nodePtr = &node;
		}
	}
	return nodePtr; // find the node
}

std::vector<Node*>* Graph::reachable(std::string n_name)
{
	for (auto &node : nodes)
	{
		node.setVisited(false);
		node.setQueued(false);
	}
	Node* startingNode = findNode(n_name);
	std::queue<Node*> bfsQueue;
	bfsQueue.push(startingNode);
	startingNode->setQueued(true);

	while (!bfsQueue.empty())
	{
		Node* current = bfsQueue.front();
		bfsQueue.pop();
		current->setVisited(true);
		for (auto &path : current->getPaths())
		{
			if (!path.getDest()->isQueued())
			{
				bfsQueue.push(path.getDest());
			}
		}
	}
	std::vector<Node*>* reachableNodes = new std::vector<Node*>;
	for (auto node : nodes)
	{
		if (node.isVisited())
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
		n.costFromStart = 999999;
		n.from = nullptr;
	}
	//std::vector<Node*>* result = new std::vector<Node*>();

	std::vector<Node*> explored;
	std::list<Node*> connectedQueue;

	explored.push_back(findNode(nameStart));
	findNode(nameStart)->setVisited(true);
	findNode(nameStart)->costFromStart = 0;
	std::cout << "Starting Node: " << nameStart << " Finishing: " << nameFinish << std::endl;
	for (const Path & path : explored[0]->getPaths())
	{
		Node* current = path.getDest();
		current->costFromStart = path.getCost();
		current->from = findNode(nameStart);
		if (!current->isVisited())
		{
			connectedQueue.push_back(current);
			current->setVisited(true);
		}
		std::cout << "Adding " << current->getName() << " to connected." << std::endl;
	}
	connectedQueue.sort(nearer);

	while (true)
	{
		if (connectedQueue.size() == 0)
		{
			std::cout << "No more connected nodes" << std::endl;

			std::vector<Node*>* nodePath = makeNodePath(nameStart, nameFinish);
			return nodePath;
		}
		else {
			Node* next = connectedQueue.front();
			connectedQueue.pop_front();
			std::cout << "Node selected is: " << next->getName() << " at: " << next->costFromStart << std::endl;

			explored.push_back(next);
			next->setVisited(true);

			if (next->getName() == nameFinish)
			{
				std::cout << "Added the destination to Explored list." << std::endl;
				std::vector<Node*>* nodePath = makeNodePath(nameStart, nameFinish);
				return nodePath;
			}

			for (Path path : next->getPaths())
			{
				Node * connected = path.getDest();
				if (!connected->isVisited())
				{

					double pathCost = path.getCost() + path.getSource()->costFromStart;
					if (pathCost < connected->costFromStart) {
						connected->from = path.getSource();
						connectedQueue.push_back(connected);
						std::cout << "Added " << connected->getName() << " to the queue.   path = " << pathCost << std::endl;
						connected->costFromStart = pathCost;
					}
				}
			}
			connectedQueue.sort(nearer);
		}
	}
	return nullptr;
}

std::vector<Node*>* Graph::makeNodePath(std::string nameStart, std::string nameFinish)
{
	std::vector<Node*>* nodePath = new std::vector<Node*>;
	Node* finalPathBackwards = findNode(nameFinish);
	while (finalPathBackwards->from != nullptr)
	{
		std::cout << "Final Path: " << finalPathBackwards->getName() << "  From:  " << finalPathBackwards->from->getName() << std::endl;
		nodePath->push_back(finalPathBackwards);
		finalPathBackwards = finalPathBackwards->from;
	}
	if (finalPathBackwards == findNode(nameStart)) {
		std::cout << "path successful" << std::endl;
		nodePath->push_back(findNode(nameStart));
		// reverse
		std::reverse(nodePath->begin(), nodePath->end());

		for (auto nde : *nodePath) {
			std::cout << "Final Path: " << nde->getName() << std::endl;
			//actualPath.push_back(reversePath[i]);
		}
	}
	return nodePath;
}

