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
	binaryTree->insertNode(1,1,0,5,6);
	binaryTree->insertNode(2,2,0,4,3);
	binaryTree->insertNode(3,3,2,-1,-1);
	binaryTree->insertNode(4,4,2,-1,8);
	binaryTree->insertNode(5,5,1,-1,-1);
	binaryTree->insertNode(6,6,1,7,-1);
	binaryTree->insertNode(7,7,6,-1,-1);
	binaryTree->insertNode(8,8,4,-1,-1);

	cout<<"layerTraversal: ";
	binaryTree->layerTraversal();//层次遍历
	cout<<endl;
	cout<<"preorderTraversal: ";
	binaryTree->preorderTraversal();//前序遍历
	cout<<endl;
	cout<<"postorderTraversal: ";
	binaryTree->postorderTraversal();//后序遍历
	cout<<endl;
	cout<<"midorderTraversal: ";
	binaryTree->midorderTraversal();//中序遍历


	int postorder[] = {5, 7, 6, 1, 8, 4, 3, 2, 0};
	int midorder[] = {5, 1, 7, 6, 0, 4, 8, 2, 3};
	int preorder[] = {0, 1, 5, 6, 7, 2, 4, 8, 3};

	delete binaryTree;
	cout<<endl<<"----------reconstruct from postoder and midorder----------"<<endl;
	binaryTree = new BinaryTree<int>();
	binaryTree->restorePost(postorder, midorder, 9);
	cout<<"layerTraversal: ";
	binaryTree->layerTraversal();//层次遍历
	cout<<endl;
	cout<<"preorderTraversal: ";
	binaryTree->preorderTraversal();//前序遍历
	cout<<endl;
	cout<<"postorderTraversal: ";
	binaryTree->postorderTraversal();//后序遍历
	cout<<endl;
	cout<<"midorderTraversal: ";
	binaryTree->midorderTraversal();//中序遍历


	delete binaryTree;
	cout<<endl<<"----------reconstruct from preoder and midorder----------"<<endl;
	binaryTree = new BinaryTree<int>();
	binaryTree->restorePre(preorder, midorder, 9);
	cout<<"layerTraversal: ";
	binaryTree->layerTraversal();//层次遍历
	cout<<endl;
	cout<<"preorderTraversal: ";
	binaryTree->preorderTraversal();//前序遍历
	cout<<endl;
	cout<<"postorderTraversal: ";
	binaryTree->postorderTraversal();//后序遍历
	cout<<endl;
	cout<<"midorderTraversal: ";
	binaryTree->midorderTraversal();//中序遍历

	return 0;
}
