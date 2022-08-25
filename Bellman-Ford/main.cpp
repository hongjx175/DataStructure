#include <iostream>
#include <list>

#define INF 1e9
using namespace std;

int d[100], n, m;
struct Edge {
	int x, y, z;
};
list<Edge> edges;

int main() {
	cin >> n >> m;
	for (int i = 0; i <= n; i++) {
		d[i] = INF;
	}
	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		edges.push_back(Edge{x, y, z});
	}
	for (int i = 1; i <= n; i++) {
		edges.push_back(Edge{0, i, 0});
	}
	d[0] = 0;
	for (int i = 0; i <= n; i++) d[i] = 0;
	for (int i = 0; i <= n + 10; i++) {
		for (auto e = edges.begin(); e != edges.end(); ++e) {
			if (d[e->y] > d[e->x] + e->z)
				d[e->y] = d[e->x] + e->z;
		}
	}
	for (auto e = edges.begin(); e != edges.end(); ++e) {
		if (d[e->y] > d[e->x] + e->z) {
			cout << e->x << "->" << e->y << endl;
			d[e->y] = d[e->x] + e->z;
			//cout << "negative cycle exists!" << endl;
		}


	}
	for (int i = 0; i <= n; i++) {
		cout << d[i] << " ";
	}
	return 0;
}

