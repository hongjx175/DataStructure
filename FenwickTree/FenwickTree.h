#ifndef FENWICKTREE_FENWICKTREE_H
#define FENWICKTREE_FENWICKTREE_H
#include <iostream>
#include <vector>
using std::vector;
class FenwickTree {
private:
	vector<int> *tree;
	int lowbit(int x) { return x & (-x); }
	int _query(int r);

public:
	FenwickTree(int *a, int n);
	~FenwickTree() {
		tree->clear();
		delete tree;
	};
	int query(int l, int r);
	void update(int x, int data);
};

FenwickTree::FenwickTree(int a[], int n) {
	tree = new vector<int>(n, 0);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j <= n; j += lowbit(j)) {
			(*tree)[j - 1] += a[i];
		}
	}
}

int FenwickTree::query(int l, int r) {
	return _query(r) - _query(l - 1);
}

int FenwickTree::_query(int r) {
	if (r == -1) return 0;
	int ans = 0;
	for (int i = r + 1; i > 0; i -= lowbit(i)) {
		ans += (*tree)[i - 1];
	}
	return ans;
}
void FenwickTree::update(int x, int data) {
	int n = tree->size();
	for (int i = x + 1; i <= n; i += lowbit(i)) {
		(*tree)[i - 1] += data;
	}
}
#endif//FENWICKTREE_FENWICKTREE_H
