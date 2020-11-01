#include "AVLTree.h"
#include <ctime>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#define random() (rand() % 51)
int main() {
	unsigned seed = time(0);
	srand(seed);

	AVLTree<int> *avlTree = new AVLTree<int>();
	int a[30];
	for (int i = 0; i < 30; i++) {
		a[i] = random();
		avlTree->ins(a[i]);
	}
	cout << "a[5] = " << a[5] << endl;
	cout << "before del(a[5])" << endl;
	avlTree->display();
	avlTree->del(a[5]);
	cout << "after del(a[5])" << endl;
	avlTree->display();
	cout << "a[10] = " << a[10] << endl;
	avlTree->del(a[10]);
	cout << "after del(a[10])" << endl;
	avlTree->display();
	delete avlTree;
	for (int i = 0; i < 100; ++i) {
		avlTree->ins(1);
	}
	cout << "The height of the tree containing 100 ones is: ***  " << avlTree->height() << "  ***" << endl;
	delete avlTree;
	return 0;
}
