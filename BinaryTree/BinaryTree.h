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
using std::max;
template<typename T>
class BinaryTree {
private:
	int root;
	struct Node{
		int id, father, lChild, rChild;
		T data;
		Node(T d, int i, int f, int l, int r){
			data = d;
			id = i;
			father = f;
			lChild = l;
			rChild = r;
		}
		friend ostream & operator << (ostream &, Node &node) {
			cout<<node.data;
			return cout;
		}
	};
	vector<Node*> tree;
public:
	BinaryTree(){
		root = -1;
	}
	void insertNode(T data, int id, int father, int lChild, int rChild);
	bool empty();
	void layerTraversal();
	void preorderTraversal();
	void postorderTraversal();
	void inorderTraversal();
	void restorePre(int preorder[], int inorder[]);
	void restorePost(int postorder[], int inorder[]);
};

template<typename T>
void BinaryTree<T>::insertNode(T data, int id, int father, int lChild, int rChild) {
	Node *node = new Node(data, id, father, lChild, rChild);
	if(father == -1) root = id;
	int maxn = max(max(lChild, rChild),father);
	if(maxn >= tree.size()){
		tree.resize(maxn+1);
	}
	if(tree.size()>id)
		tree[id] = node;
	else tree.push_back(node);
}
template<typename T>
bool BinaryTree<T>::empty() {
	return tree.empty();
}

//按层次遍历
template<typename T>
void BinaryTree<T>::layerTraversal() {
	if(tree.empty()) return;
	Queue<int>* queue = new Queue<int>();
	queue->pushback(root);
	while (!queue->empty()){
		Node *cur = tree[queue->front()];
		queue->pop();
		cout<<*cur<<"  ";
		(cur->lChild != -1)?(queue->pushback(cur->lChild)):void();
		(cur->rChild != -1)?(queue->pushback(cur->rChild)):void();
	}
}
//先序遍历
template<typename T>
void BinaryTree<T>::preorderTraversal() {
	if(tree.empty()) return;
	Stack<int>* stack = new Stack<int>();
	Node *cur = tree[root];

	while(true){
		cout<<*cur<<"  ";
		if(cur->rChild != -1){
			stack->push(cur->rChild);
		}
		if(cur->lChild != -1){
			cur = tree[cur->lChild];
		} else{
			if(stack->empty()) break;
			cur = tree[stack->top()];
			stack->pop();
		}
	}
}
//后序遍历
template<typename T>
void BinaryTree<T>::postorderTraversal() {
	if(tree.empty()) return;
	Stack<int>* stack = new Stack<int>();
	
}
//中序遍历
template<typename T>
void BinaryTree<T>::inorderTraversal() {

}
template<typename T>
void BinaryTree<T>::restorePost(int *postorder, int *inorder) {
}
template<typename T>
void BinaryTree<T>::restorePre(int *preorder, int *inorder) {
}
#endif//BINARYTREE_BINARYTREE_H
