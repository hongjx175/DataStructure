#include <iostream>
#include "Graph.h"

int main() {
	Graph *graph = new Graph();
	int n, m, source;
	cin >> n >> m >> source;
	while (m--) {
		int x, y, z;
		cin >> x >> y >> z;
		graph->addEdge(x, y, z);
	}
	graph->Dijkstra(source);

	return 0;
}
