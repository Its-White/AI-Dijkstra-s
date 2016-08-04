#pragma once
#include<list>
#include<string>
#include<vector>
#include<queue>
#include "MathsLibrary.h"
#include "Texture.h"
class Node;

class Path
{
public:
	Path();
	Path(Node* start, Node* dest, int newCost);
	~Path();
	Node* getSource() const { return source; };
	Node* getDest() const { return destination; };
	int getCost() const { return cost; };

private:
	float cost;
	Node *source;
	Node *destination;
};


struct coord
{
	coord() {};
	coord(int inx, int iny);
	int x, y;
};

class Node
{
public:
	Node();
	Node(std::string newName, Vector2 pos);
	~Node();
	std::string getName() const { return name; };
	void addPath(Path newPath);
	bool isVisited() { return visited; };
	void setVisited(bool v);
	bool isQueued() { return queued; };
	void setQueued(bool q);
	const std::list<Path> & getPaths() { return paths; };
	Vector2 getPosition() { return position; };
	coord getPositionOnMap() { return positionOnMap; };

	double costFromStart;
	double heuristic;
	Node* from;

private:
	std::string name;
	std::list<Path> paths;
	Vector2 position;
	coord positionOnMap;
	bool visited;
	bool queued;
};

class Graph
{
public:
	Graph();
	~Graph();

	void addNode(std::string name, Vector2 pos);
	void loadNodeImage(std::string n_name, std::string fileName);
	void addPath(std::string source, std::string destination, int cost);
	Vector2 getNodeLocation(std::string n_name);
	Node* findNode(std::string n_name);
	Node* findScreenNode(coord m_map);
	std::vector<Node*>* reachable(std::string n_name);
	std::vector<Node*>* shortestPath(std::string nameStart, std::string nameFinish); //Dijkstra's shortest path is implemented here

private:
	std::list<Node> nodes;

	Vector2 position;

	std::string spriteFile;
	Texture* m_sprite;
	std::vector<Node*>* makeNodePath(std::string nameStart, std::string nameFinish);
};
