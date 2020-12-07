#ifndef MST_FLEURY_ALGOONGRAPH_H
#define MST_FLEURY_ALGOONGRAPH_H

#include "Graph.h"

using std::swap;

class AlgoOnGraph {
private:
	vector<int> father;
	vector<int> size;

	int findSet(int x) {
		return father[x] == x ? x : father[x] = findSet(father[x]);
	}

	void unionSet(int x, int y) {
		size[x] > size[y] ? swap(x, y) : void();
		father[x] = y;
		size[y] += size[x];
	}

	static bool comp(const Edge &a, const Edge &b) {
		return a.x < b.x;
	}

public:
	void Kruskal(Graph *graph);

	void Fleury(Graph *graph);
};


void AlgoOnGraph::Kruskal(Graph *graph) {
	father.resize(graph->numPoints);
	size.resize(graph->numPoints, 1);
	for (int i = 0; i < father.size(); i++) {
		father[i] = i;
	}
	vector<Edge> MST;
	vector<Edge> E = graph->E;
	sort(E.begin(), E.end());
	for (auto edge = E.begin(); edge != E.end(); ++edge) {
		int fatherX = findSet(edge->x);
		int fatherY = findSet(edge->y);

		if (fatherX == fatherY)
			continue;
		else {
			MST.push_back(*edge);
			unionSet(fatherX, fatherY);
		}
	}
	std::sort(MST.begin(), MST.end(), comp);
	double sum = 0;
	for (int i = 0; i < MST.size(); i++) {
		sum += MST[i].weight;
		std::cout << MST[i].x << "  " << MST[i].y << std::endl;
	}
	std::cout << sum << std::endl;
}

void AlgoOnGraph::Fleury(Graph *graph) {

}

#endif //MST_FLEURY_ALGOONGRAPH_H
