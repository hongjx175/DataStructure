#include <iostream>
#include "Graph.h"
#include "AlgoOnGraph.h"

using namespace std;

int main() {
	int n, m;
	int source, sink;
	cin >> n >> m;
	cin >> source >> sink;

	Graph *graph = new Graph(n, m);
	AlgoOnGraph *algoOnGraph = new AlgoOnGraph();
	for (int i = 0; i < m; i++) {
		int a, b, capacity;
		cin >> a >> b >> capacity;
		graph->add(a - 1, b - 1, capacity);
	}


	int maxflow = algoOnGraph->maxflow_FordFulkerson(graph, source - 1, sink - 1);
	cout << maxflow << endl;
	return 0;
}
