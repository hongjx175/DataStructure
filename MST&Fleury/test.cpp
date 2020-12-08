#include <iostream>
#include "Graph.h"
#include "AlgoOnGraph.h"

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	Graph *graph = new Graph(n, m);
	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		graph->add(x, y, z);
	}
	AlgoOnGraph *algoOnGraph = new AlgoOnGraph();
	algoOnGraph->Kruskal(graph);
	algoOnGraph->Fleury(graph);
	return 0;
}
