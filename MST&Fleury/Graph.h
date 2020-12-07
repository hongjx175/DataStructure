#ifndef MST_FLEURY_GRAPH_H
#define MST_FLEURY_GRAPH_H

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using std::vector;

struct Edge {
	int x, y;
	double weight;

	bool operator<(const Edge edge) const {
		return weight < edge.weight;
	}
};


class Graph {
private:
	int numPoints;
	vector<Edge> E;
public:
	Graph(int n, int m) {
		numPoints = n;
		E.resize(m);
	}

	~Graph() {}

	void add(int x, int y, double weight);

	friend class AlgoOnGraph;//友元类

};

void Graph::add(int x, int y, double weight) {
	if (x > y) std::swap(x, y);
	E.push_back(Edge{x, y, weight});
}

#endif //MST_FLEURY_GRAPH_H
