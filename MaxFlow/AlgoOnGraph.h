//
// Created by 86185 on 2020/12/14.
//

#ifndef MAXFLOW_ALGOONGRAPH_H
#define MAXFLOW_ALGOONGRAPH_H

#include "Graph.h"

#define INF 0x7fffffff

class AlgoOnGraph {
public:
	int maxflow_FordFulkerson(Graph *graph, int source, int sink);

	int maxflow_EdmondsKarp(Graph *graph, int source, int sink);

	int maxflow_Dinic(Graph *graph, int source, int sink);

private:
	int dfs(Graph *graph, int s, int t, int flow);

	vector<bool> used;
};

int AlgoOnGraph::dfs(Graph *graph, int s, int t, int flow) {
	if (s == t) return flow;
	for (int i = graph->head[s]; i; i = graph->nxt[i]) {
		if (graph->capacity[i] <= 0 && used[graph->to[i]]) continue;
		used[graph->to[i]] = true;
		int df = dfs(graph, graph->to[i], t, std::min(flow, graph->capacity[i]));
		if (df > 0) {
			graph->capacity[i] -= df;
			graph->capacity[i ^ 1] += df;
			return df;
		}
	}
}

int AlgoOnGraph::maxflow_FordFulkerson(Graph *graph, int source, int sink) {
	int flow = 0, augmentation;
	used.resize(graph->numPoints, false);
	do {
		used.resize(used.size(), false);
		augmentation = dfs(graph, source, sink, INF);
		flow += augmentation;
	} while (augmentation > 0);

	return flow;
}

int AlgoOnGraph::maxflow_EdmondsKarp(Graph *graph, int source, int sink) {

}

int AlgoOnGraph::maxflow_Dinic(Graph *graph, int source, int sink) {
	return 0;
}


#endif //MAXFLOW_ALGOONGRAPH_H
