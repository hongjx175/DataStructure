#include <iostream>
#include "Graph.h"
#include "AlgoOnGraph.h"

using namespace std;

int main() {
	//点标号从0开始
	int n, m, source, sink;
	cin >> n >> m >> source >> sink;

	Graph *graph = new Graph(n, m);
	AlgoOnGraph *algoOnGraph = new AlgoOnGraph();
	for (int i = 0; i < m; i++) {
		int a, b, capacity;
		cin >> a >> b >> capacity;
		graph->add(a, b, capacity);
	}

	Graph *graph1 = new Graph(graph);
	int maxflow1 = algoOnGraph->maxflow_FordFulkerson(graph, source, sink);
	int maxflow2 = algoOnGraph->maxflow_EdmondsKarp(graph1, source, sink);
	cout << "maxflow computated by FordFulkerson: " << maxflow1 << endl;
	cout << "maxflow computated by EdmondsKarp: " << maxflow2 << endl;
	return 0;
}
