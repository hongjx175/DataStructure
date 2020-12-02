//
// Created by 86185 on 2020/12/2.
//

#ifndef DIJKSTRA_GRAPH_H
#define DIJKSTRA_GRAPH_H

#include <map>
#include <set>
#include <queue>

using namespace std;

class Graph {
private:
	map<int, set<pair<double, int>>> *graph;
	map<int, double> *dis;
	map<int, int> *pre;

	void init(int source);

public:
	Graph();

	~Graph();

	void addEdge(int s, int t, double weight);

	void Dijkstra(int s);
	/*void show() {
		for (auto it = (*graph)[1].begin(); it != (*graph)[1].end(); ++it) {
			cout << it->first << "  " << it->second << endl;
		}
	}*/
};

Graph::Graph() {
	graph = new map<int, set<pair<double, int>>>();
	dis = new map<int, double>();
	pre = new map<int, int>();
}

Graph::~Graph() {
	graph->clear();
	dis->clear();
	pre->clear();
	delete graph;
	delete dis;
	delete pre;
}

void Graph::addEdge(int s, int t, double weight) {
	(*graph)[s].insert(make_pair(weight, t));
}

void Graph::init(int source) {
	dis->clear();
}

void Graph::Dijkstra(int s) {
	init(s);
	priority_queue<pair<double, int>> *priorityQueue = new priority_queue<pair<double, int>>();
	priorityQueue->push(make_pair(1, 2));
	priorityQueue->push(make_pair(2, 1));
	while (!priorityQueue->empty()) {
		auto p = priorityQueue->top();
		priorityQueue->pop();
		cout << p.first << endl;
	}


}

#endif //DIJKSTRA_GRAPH_H
