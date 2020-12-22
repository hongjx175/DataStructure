#include "2_3Tree.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
	Tree2_3<int> *tree23 = new Tree2_3<int>();
	for (int i = 1; i <= 20; i++)
		tree23->ins(i);
	tree23->display();
	cout << "\nrank(8) before delete: " << tree23->rank(8) << endl;
	tree23->del(6);
	tree23->display();
	cout << "\nrank(8) after delete (6): " << tree23->rank(8) << endl;
	return 0;
}
