#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H
#include "Queue.h"
#include <vector>
using std::cout;
using std::vector;
using std::ostream;
using std::max;
using std::endl;
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
	~BinaryTree(){
	}
	void insertNode(T data, int id, int father, int lChild, int rChild);
	bool empty();
	void layerTraversal();
	void preorderTraversal();
	void postorderTraversal();
	void midorderTraversal();
	int restorePre(int preorder[], int midorder[], int len, int father=-1);
	int restorePost(int postorder[], int midorder[], int len, int father=-1);
};

template<typename T>
void BinaryTree<T>::insertNode(T data, int id, int father, int lChild, int rChild) {
	int maxn = max(max(lChild, rChild),max(father, id));
	if(maxn >= tree.size()){
		tree.resize(maxn+1);
	}
	Node *node = new Node(data, id, father, lChild, rChild);
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
			while(!stack->empty() && ((cur->id==(tree[stack->top()])->lChild) || (cur->id==(tree[stack->top()])->rChild))){
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
void BinaryTree<T>::midorderTraversal() {
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
int BinaryTree<T>::restorePost(int *postorder, int *midorder, int len, int father) {
	if(postorder == NULL || midorder == NULL || len < 1) return NULL;

	//后根遍历的最后一个值就是根节点
	int rootKey = *(postorder+len-1);
	//cout<<"rootKey: "<<rootKey<<endl;
	int leftLen = 0;
	int *rootMidorder = midorder;

	//在中根遍历（中序遍历）中找到根节点
	while(*rootMidorder != rootKey && rootMidorder<=midorder+len-1){
		rootMidorder++;
		leftLen++;
	}
	if(*rootMidorder != rootKey)
		return NULL;

	int lChild = -1, rChild = -1;
	if(leftLen > 0){
		lChild = restorePost(postorder, midorder, leftLen, rootKey);//左
	}
	if(len - leftLen - 1 > 0){
		rChild = restorePost(postorder+leftLen,rootMidorder+1 ,len-leftLen-1, rootKey);//右
	}
	this->insertNode(rootKey, rootKey, father, lChild, rChild);
	return rootKey;
}
template<typename T>
int BinaryTree<T>::restorePre(int *preorder, int *midorder, int len, int father) {
	if(preorder == NULL || midorder == NULL || len < 1) return NULL;

	//先根遍历的第一个值就是根节点
	int rootKey = *(preorder+0);
	//cout<<"rootKey: "<<rootKey<<endl;
	int leftLen = 0;
	int *rootMidorder = midorder;

	//在中序遍历中找到根节点
	while(*rootMidorder != rootKey && rootMidorder<=midorder+len-1){
		rootMidorder++;
		leftLen++;
	}
	if(*rootMidorder != rootKey)
		return NULL;

	int lChild = -1, rChild = -1;
	if(leftLen > 0){
		lChild = restorePre(preorder+1, midorder, leftLen, rootKey);//左
	}
	if(len - leftLen - 1 > 0){
		rChild = restorePre(preorder+leftLen+1,rootMidorder+1 ,len-leftLen-1, rootKey);//右
	}
	this->insertNode(rootKey, rootKey, father, lChild, rChild);
	return rootKey;
}
#endif//BINARYTREE_BINARYTREE_H
