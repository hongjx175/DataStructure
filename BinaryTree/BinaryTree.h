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
		int id;
		Node *father, *lChild, *rChild;
		T data;
		Node(T d, int i, Node *f, Node *l, Node *r){
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
	~BinaryTree(){
		delete tree;
		tree = nullptr;
	}
	void insertNode(T data, int id, int father, int lChild, int rChild);
	bool empty();
	void layerTraversal();
	void preorderTraversal();
	void postorderTraversal();
	void inorderTraversal();
	BinaryTree<T>* restorePre(int preorder[], int inorder[], int len);
	BinaryTree<T>* restorePost(int postorder[], int inorder[], int len);
};

template<typename T>
void BinaryTree<T>::insertNode(T data, int id, int father, int lChild, int rChild) {
	int maxn = max(max(lChild, rChild),max(father, id));
	if(maxn >= tree.size()){
		tree.resize(maxn+1);
	}
	Node *node = new Node(data, id, tree[father], tree[lChild], tree[rChild]);
	if(father == -1) root = id;
	tree[id] = node;
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
/* //方法一
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
 */
	//方法二
	stack->push(root);
	while(!stack->empty()){
		cur = tree[stack->top()];
		stack->pop();
		cout<<*cur<<"  ";
		(cur->rChild != -1)?stack->push(cur->rChild):void();
		(cur->lChild != -1)?stack->push(cur->lChild):void();

	}
}
//后序遍历
template<typename T>
void BinaryTree<T>::postorderTraversal() {
	if(tree.empty()) return;
	Stack<int>* stack = new Stack<int>();
	Node *cur = tree[root];
	stack->push(root);
	while(!stack->empty()){
		if(cur->lChild == -1 && cur->rChild ==-1){
			cout<<*cur<<"  ";
			stack->pop();
			//叶结点出栈后，若栈顶为出栈的叶结点的父亲，继续出战
			while(!stack->empty() && (cur->father==stack->top())){
				cur = tree[stack->top()];
				cout<<*cur<<"  ";
				stack->pop();
			}
		}else{
			//先右后左
			(cur->rChild != -1)?stack->push(cur->rChild):void();
			(cur->lChild != -1)?stack->push(cur->lChild):void();
		}

		if(!stack->empty()) cur = tree[stack->top()];
	}
	
}
//中序遍历
template<typename T>
void BinaryTree<T>::inorderTraversal() {
	if(tree.empty()) {
		cout<<"empty";
		return;
	}
	Stack<int>* stack = new Stack<int>();
	Node *cur = tree[root];
	while (!stack->empty() || cur != nullptr){
		while(cur != nullptr){
			stack->push(cur->id);
			cur = (cur->lChild != -1)?tree[cur->lChild]: nullptr;
		}
		cur = tree[stack->top()];
		cout<<*cur<<"  ";
		stack->pop();
		cur = (cur->rChild != -1)?tree[cur->rChild]: nullptr;
	}
}
template<typename T>
BinaryTree<T>* BinaryTree<T>::restorePost(int *postorder, int *inorder, int len) {

}
template<typename T>
BinaryTree<T>* BinaryTree<T>::restorePre(int *preorder, int *inorder, int len) {
}
#endif//BINARYTREE_BINARYTREE_H
