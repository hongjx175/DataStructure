#include "AVLTree.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main() {
	AVLTree<int> *avlTree = new AVLTree<int>();
	avlTree->ins(5);
	avlTree->ins(4);
	avlTree->ins(1);
	avlTree->display();
	avlTree->ins(3);
	avlTree->ins(3);
	avlTree->ins(3);
	avlTree->display();
	avlTree->ins(2);
	avlTree->ins(3);
	avlTree->ins(3);
	avlTree->ins(3);
	avlTree->ins(3);
	avlTree->ins(3);
	avlTree->ins(3);
	avlTree->ins(3);
	avlTree->display();
	return 0;
}
