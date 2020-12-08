//
// Created by hongjx175 on 2020/12/2.
//

#ifndef DIJKSTRA_GRAPH_H
#define DIJKSTRA_GRAPH_H

#include <map>
#include <set>
#include <queue>

using namespace std;

class Graph {
private:
	map<int, vector<pair<double, int>>> *graph;
	set<int> *points;
	map<int, int> *pre;

	const int INF = 2147483647;

	void init(int source, map<int, double> *dis, map<int, bool> *unused);

	void showPath(int point);

public:
	Graph();

	~Graph();

	void addEdge(int s, int t, double weight);

	void Dijkstra(int s);
};

Graph::Graph() {
	graph = new map<int, vector<pair<double, int>>>();
	points = new set<int>();
	pre = new map<int, int>();
}

Graph::~Graph() {
	graph->clear();
	pre->clear();
	points->clear();
	delete graph;
	delete pre;
	delete points;
}

void Graph::addEdge(int s, int t, double weight) {
	(*graph)[s].push_back(make_pair(weight, t));
	points->insert(s);
	points->insert(t);
}

void Graph::init(int source, map<int, double> *dis, map<int, bool> *unused) {
	(*pre)[source] = -1;
	for (auto item = points->begin(); item != points->end(); ++item)
		(*dis)[*item] = INF, (*unused)[*item] = true;
	(*dis)[source] = 0;
}

void Graph::Dijkstra(int source) {

	//每次往优先队列里添加新的状态，保证时间复杂度为O(nlog(n+m))

	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> *priorityQueue
			= new priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>>();
	map<int, double> *dis = new map<int, double>();
	map<int, bool> *unused = new map<int, bool>;
	init(source, dis, unused);
	for (auto item = dis->begin(); item != dis->end(); ++item)
		priorityQueue->push(make_pair(item->second, item->first));

	while (!priorityQueue->empty()) {
		pair<double, int> point = priorityQueue->top();
		priorityQueue->pop();
		while ((*unused)[point.second] == false && !priorityQueue->empty()) {
			point = priorityQueue->top();
			priorityQueue->pop();
		}
		if (priorityQueue->empty()) break;
		(*unused)[point.second] = false;//用于更新其他的点
		vector<pair<double, int>> linkEdges = (*graph)[point.second];
		for (auto edge = linkEdges.begin(); edge != linkEdges.end(); ++edge) {
			if ((*dis)[edge->second] > (*dis)[point.second] + edge->first) {
				(*pre)[edge->second] = point.second;
				(*dis)[edge->second] = (*dis)[point.second] + edge->first;
				priorityQueue->push(make_pair((*dis)[edge->second], edge->second));
				//(*unused)[edge->second] = true;
			}
		}
	}
	for (auto item = dis->begin(); item != dis->end(); ++item) {
		cout << "distance from " << source << " to " << item->first << " : **" << item->second << "**";
		cout << "    The path is :";
		showPath(item->first);
		cout << endl;
	}
	dis->clear();
	unused->clear();
	delete dis;
	delete unused;
}

void Graph::showPath(int point) {
	if (point == -1) return;
	showPath((*pre)[point]);
	cout << point << "  ";
}

#endif //DIJKSTRA_GRAPH_H
