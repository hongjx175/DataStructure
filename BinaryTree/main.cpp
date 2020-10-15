#include "BinaryTree.h"
#include "Stack.h"
#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;
using std::cin;
int main() {
	BinaryTree<int>* binaryTree = new BinaryTree<int>();
	//BinaryTree<T>::insertNode(T data, int Id, int father, int lChild, int rChild)
	binaryTree->insertNode(0,0,-1,1,2);
	binaryTree->insertNode(1,1,0,-1,4);
	binaryTree->insertNode(2,2,0,3,-1);
	binaryTree->insertNode(3,3,2,-1,-1);
	binaryTree->insertNode(4,4,1,-1,-1);
	binaryTree->layerTraversal();
	cout<<endl;
	binaryTree->preorderTraversal();
	return 0;
}
