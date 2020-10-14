//
// Created by 86185 on 2020/10/14.
//

#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H
#include "Queue.h"
#include <vector>
using std::cout;
using std::vector;
using std::ostream;
template<typename T>
class BinaryTree{
private:
	struct Node{
		T data;
		Node *lChild, *rChild;
		Node(T data0){
			data = data0;
			lChild = nullptr;
			rChild = nullptr;
		}
		friend ostream & operator << (ostream &, Node &node) {
			cout<<node.data;
			return cout;
		}
	};
	vector<Node*> tree;
public:
	BinaryTree(){
		//tree = new vector<T*>();
	}
	void insertNode(T data);
	bool empty();
	void layerTraversal();
};
template<typename T>
void BinaryTree<T>::insertNode(T data) {
	Node *node = new Node(data);
	tree.push_back(node);
	int len = tree.size();
	if(len == 1) return;
	Node *father = tree[len/2-1];
	(father->lChild == nullptr)?(father->lChild=node):(father->rChild=node);

}
template<typename T>
bool BinaryTree<T>::empty() {
	return tree.empty();
}

template<typename T>
void BinaryTree<T>::layerTraversal() {
	if(tree.empty()) return;
	Node *root = tree[0];
	Queue<Node*> *queue = new Queue<Node*>();
	queue->pushback(root);
	while(!queue->empty()){
		Node *f = queue->front();
		cout<<*f<<"  ";
		queue->pop();

	}
}


#endif//BINARYTREE_BINARYTREE_H
