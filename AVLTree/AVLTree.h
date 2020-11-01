//
// Created by 86185 on 2020/10/26.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H
#include "Stack.h"
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
template<typename T>
class AVLTree {
private:
	struct Node {
		Node *leftSon, *rightSon, *father;
		int height;
		T data;
		Node(T idata = NULL) {
			height = 1;
			leftSon = rightSon = father = nullptr;
			data = idata;
		}
		friend ostream &operator<<(ostream &, Node &node) {
			cout << node.data;
			return cout;
		}
	};
	Node *root;
	void leftRotate(Node *node);
	void rightRotate(Node *node);
	int max(int a, int b) {
		return a > b ? a : b;
	}
	int getHeight(Node *node) {
		return node == nullptr ? 0 : node->height;
	}
	bool updateHeight(Node *node);
	void update(Node *node);
	void _display(Node *node);

public:
	AVLTree() {
		root = nullptr;
	}
	~AVLTree() {
	}
	void ins(T data);
	void display();
};
template<typename T>
bool AVLTree<T>::updateHeight(Node *node) {
	if (node == nullptr) return false;
	int height = getHeight(node);
	node->height = max(getHeight(node->leftSon), getHeight(node->rightSon)) + 1;
	if (height < node->height) return true;
	return false;
}
template<typename T>
void AVLTree<T>::leftRotate(Node *node) {
	Node *father = node->father, *son = node->rightSon;
	if (father != nullptr) {
		if (node->data < father->data) {//左儿子
			father->leftSon = son;
			node->rightSon = son->leftSon;
			son->leftSon = node;
			(node->rightSon)->father = node;
		} else {
			/*father->rightSon = node->rightSon;
			(node->rightSon)->father = father;
			Node *tmp = (node->rightSon)->leftSon;
			node->rightSon = tmp;
			if (tmp) tmp->father = node;
			(father->rightSon)->leftSon = node;
			node->father = father->rightSon;*/
			father->rightSon = son;
			node->rightSon = son->leftSon;
			son->leftSon = node;
			(node->rightSon)->father = node;
		}
		node->father = son;
		son->father = father;

		updateHeight(node);
		updateHeight(son);
		updateHeight(father);

	} else {
		root = node->rightSon;
		node->rightSon = root->leftSon;
		(root->leftSon)->father = node;
		root->leftSon = node;
		node->father = root;
		updateHeight(node);
		updateHeight(root);
	}
}
template<typename T>
void AVLTree<T>::rightRotate(Node *node) {
	Node *father = node->father;


	bool lrFlag = false;
	if (father != nullptr) {
		if (node->data < father->data) {
			father->leftSon = node->leftSon;
			(node->leftSon)->father = father;
			Node *tmp = (node->leftSon)->rightSon;
			node->leftSon = tmp;
			tmp->father = node;
			(father->leftSon)->rightSon = node;
			node->father = father->leftSon;
		} else {
			father->rightSon = node->leftSon;
			(node->leftSon)->father = father;
			Node *tmp = (node->leftSon)->rightSon;
			node->leftSon = tmp;
			tmp->father = node;
			(father->rightSon)->rightSon = node;
			node->father = father->rightSon;
			lrFlag = true;
		}
		updateHeight(node);
		(lrFlag) ? updateHeight(father->rightSon) : updateHeight(father->leftSon);
		updateHeight(father);

	} else {
		root = node->leftSon;
		node->leftSon = root->rightSon;
		if (root->rightSon) (root->rightSon)->father = node;
		root->rightSon = node;
		node->father = root;
		updateHeight(node);
		updateHeight(root);
	}
}
template<typename T>
void AVLTree<T>::update(Node *node) {
	while (node != nullptr) {
		if (getHeight(node->leftSon) - getHeight(node->rightSon) > 1) {
			Node *son = node->leftSon;
			if (getHeight(son->leftSon) >= getHeight(son->rightSon)) {
				rightRotate(node);
			} else {
				leftRotate(son);
				rightRotate(node);
			}
		} else if (getHeight(node->rightSon) - getHeight(node->leftSon) > 1) {
			Node *son = node->rightSon;
			if (getHeight(son->leftSon) > getHeight(son->rightSon)) {
				rightRotate(son);
				leftRotate(node);
			} else {
				leftRotate(node);
			}
		}
		bool flag = updateHeight(node);
		if (!flag) break;
		node = node->father;
	}
}
template<typename T>
void AVLTree<T>::ins(T data) {
	if (root == nullptr) {
		root = new Node(data);
		return;
	}
	Node *newNode = new Node(data);
	Node *node = root;
	while (node != nullptr) {
		if (data < node->data) {
			if (node->leftSon != nullptr) {
				node = node->leftSon;
			} else {
				newNode->father = node;
				node->leftSon = newNode;
				update(node);
				break;
			}
		} else {
			if (node->rightSon != nullptr) {
				node = node->rightSon;
			} else {
				newNode->father = node;
				node->rightSon = newNode;
				update(node);
				break;
			}
		}
	}
}
template<typename T>
void AVLTree<T>::display() {
	_display(root);
	cout << endl;
}
template<typename T>
void AVLTree<T>::_display(Node *node) {
	(node->leftSon != nullptr) ? _display(node->leftSon) : void();
	//cout << node->height << "  " << getHeight(node->leftSon) << "  " << getHeight(node->rightSon) << endl;
	cout << *node << "  ";
	(node->rightSon != nullptr) ? _display(node->rightSon) : void();
}
#endif//AVLTREE_AVLTREE_H
