#include "BST.h"
#include <ctime>
#include <iostream>
using std::cin;
using std::cout;
#define random() (rand() % 201 - 100)
int main() {
	unsigned seed = time(0);
	srand(seed);
	BST<int> *bst = new BST<int>();
	//int a[30] = {-1, -80, -61, -60, 63, -53, -13, -52, -49, 88, -81, 22, -31, -16, -15, 13, 17, 21, 47, 26, 38, 44, -53, 77, 83, 85, 90};
	int a[30];
	for (int i = 0; i < 30; i++) {
		a[i] = random();
		bst->ins(a[i]);
	}
	cout << "a[5] = " << a[5] << endl;
	cout << "before del(a[5])" << endl;
	bst->display();
	bst->del(a[5]);
	cout << "after del(a[5])" << endl;
	bst->display();
	cout << "a[10] = " << a[10] << endl;
	bst->del(a[10]);
	cout << "after del(a[10])" << endl;
	bst->display();
	cout << "The 7th max element: " << bst->getData(7) << endl;
	return 0;
}
