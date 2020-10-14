#include <iostream>
#include "BinaryTree.h"
#include <vector>
using std::vector;
using std::cout;
using std::endl;
using std::cin;
int main() {
	cout<<"Please enter data in a hierarchical order"<<endl;
	BinaryTree<int>* binaryTree = new BinaryTree<int>();
	binaryTree->insertNode(1);
	binaryTree->layerTraversal();

	return 0;
}
