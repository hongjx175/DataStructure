//
// Created by 86185 on 2020/12/14.
//

#ifndef MAXFLOW_GRAPH_H
#define MAXFLOW_GRAPH_H

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
	//vector<Edge> E;
	vector<int> head, nxt, to, capacity;
	int tot;
public:
	Graph(int n, int m) {
		numPoints = n;
		tot = 1;
		head.resize(n);
		nxt.resize(2 * m + 2, 0);
		to.resize(2 * m + 2);
		capacity.resize(2 * m + 2);
	}

	~Graph() {}

	void add(int x, int y, double weight);

	friend class AlgoOnGraph;//友元类

};

void Graph::add(int x, int y, double weight) {
	nxt[++tot] = head[x], head[x] = tot, to[tot] = y, capacity[tot] = weight;//添加边
	std::swap(x, y);
	nxt[++tot] = head[x], head[x] = tot, to[tot] = y, capacity[tot] = 0;

}

#endif //MAXFLOW_GRAPH_H
