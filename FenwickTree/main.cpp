#include "FenwickTree.h"
#include <ctime>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#define random() (rand() % 7)
int main() {
	unsigned seed = time(0);
	srand(seed);
	int a[300];
	cout << "a[]: ";
	for (int i = 0; i < 20; i++) {
		a[i] = random();
		cout << a[i] << "  ";
	}
	FenwickTree *fenwickTree = new FenwickTree(a, 20);
	cout << "\nquery(0, 5): " << fenwickTree->query(0, 5) << endl;
	fenwickTree->update(3, 1);
	cout << "after a[3] adding 1, query(0, 5): " << fenwickTree->query(0, 5) << endl;
	delete fenwickTree;
	return 0;
}
