#ifndef MST_FLEURY_ALGOONGRAPH_H
#define MST_FLEURY_ALGOONGRAPH_H

#include "Graph.h"
#include <queue>

using std::queue;
using std::swap;
using std::pair;
using std::make_pair;

class AlgoOnGraph {
private:
	vector<int> father;
	vector<int> size;

	void makeSet(int numPoints) {
		father.resize(numPoints);
		size.resize(numPoints, 1);
		for (int i = 0; i < father.size(); i++) {
			father[i] = i;
		}
	}

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

	bool checkCut(int x, int y, int i, int[], int[], int[], bool[], int);

public:
	void Kruskal(Graph *graph);

	void Fleury(Graph *graph);

};


void AlgoOnGraph::Kruskal(Graph *graph) {
	makeSet(graph->numPoints);
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
	std::cout << "Edges in the minimum spanning tree: " << std::endl;
	double sum = 0;
	for (int i = 0; i < MST.size(); i++) {
		sum += MST[i].weight;
		std::cout << MST[i].x << "  " << MST[i].y << std::endl;
	}
	std::cout << "Sum weight of the minimum spanning tree: " << sum << std::endl << std::endl;
}

void AlgoOnGraph::Fleury(Graph *graph) {
	const int M = graph->E.size() * 2 + 2;

	int head[graph->numPoints], to[M], nxt[M], tot = 1;//邻接表存图，支持O(1)删边
	bool used[M];
	for (int i = 0; i < graph->numPoints; i++) head[i] = 0;
	for (int i = 0; i < M; i++) used[i] = false;

	for (auto edge = graph->E.begin(); edge != graph->E.end(); ++edge) {
		int x = edge->x, y = edge->y;
		nxt[++tot] = head[x], head[x] = tot, to[tot] = y;//添加边
		swap(x, y);
		nxt[++tot] = head[x], head[x] = tot, to[tot] = y;
	}
	queue<int> que;
	que.push(0);
	int m = graph->E.size();
	while (m--) {
		int x = que.back(), y = x, tempy = x, i, tempi;
		for (i = head[x]; i; i = nxt[i]) {
			if (used[i]) continue;
			tempy = to[i], tempi = i;
			//检测是否为割边
			if (!checkCut(x, tempy, tot, head, nxt, to, used, graph->numPoints)) {
				y = tempy;
				used[i] = true, used[i ^ 1] = true;//O(1)删边，双向边在此种存图方式里下标相邻
				break;
			}
		}
		if (y == x) {
			y = tempy;
			used[tempi] = true, used[tempi ^ 1] = true;//O(1)删边
		}
		que.push(y);
	}
	std::cout << "Path of  Eluer circuit: \n";
	while (!que.empty()) {
		std::cout << que.front();
		if (que.size() > 1) std::cout << " -> ";
		que.pop();
	}
}

//检查是否为G-{...}的割边
bool AlgoOnGraph::checkCut(int x, int y, int tot, int *head, int *nxt, int *to, bool used[], int numPoints) {
	makeSet(numPoints);
	for (int i = 0; i < numPoints; i++) {
		for (int j = head[i]; j; j = nxt[j]) {
			if (used[j]) continue;
			int xx = i, yy = to[j];
			if ((xx == x && yy == y) || (xx == y && yy == x)) continue;
			int fatherxx = findSet(xx), fatheryy = findSet(yy);
			if (fatherxx != fatheryy) {
				unionSet(fatheryy, fatherxx);
			}
		}
	}
	return findSet(x) != findSet(y);
}

#endif //MST_FLEURY_ALGOONGRAPH_H
