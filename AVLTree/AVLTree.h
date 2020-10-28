//
// Created by 86185 on 2020/10/26.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H
#include "Stack.h"
#include <iostream>
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
	};
	Node *root;
	void leftRotate(Node *node, Node *father);
	void rightRotate(Node *node, Node *father);
	int max(int a, int b) { return a > b ? a : b; }
	int getHeight(Node *node) { return node == nullptr ? 0 : node->height; }
	bool updateHeight(Node *node) {
		int height = getHeight(node);
		node->height = max(getHeight(node->leftSon), getHeight(node->rightSon)) + 1;
		if (height < node->height) return true;
		return false;
	}
	void update(Node *node);

public:
	AVLTree() {
		root = nullptr;
	}
	~AVLTree() {
	}
	void ins(T data);
};
template<typename T>
void AVLTree<T>::update(Node *node) {
}
template<typename T>
void AVLTree<T>::ins(T data) {
	if (root == nullptr) {
		root = new Node(data);
		return;
	}
	bool add_height = false;
	Stack<Node *> *stack = new Stack<Node *>();
	stack->push(root);
	Node *node = root;
	while (node != nullptr) {
		stack->push(node);
		if (data < node->data) {
			if (node->leftSon != nullptr) {
				node = node->leftSon;
			} else {
				node->leftSon = new Node(data);
				if (node->height == 1) {
					add_height = true;
				}
				break;
			}
		} else {
			if (node->rightSon != nullptr) {
				node = node->rightSon;
			} else {
				node->rightSon = new Node(data);
				if (node->height == 1) {
					add_height = true;
				}
				break;
			}
		}
	}


	while (add_height && !stack->empty()) {
		node = stack->top();
		stack->pop();
		Node *father = nullptr;
		if (!stack->empty()) father = stack->top();

		int leftHeight = getHeight(node->leftSon);
		int rightHeight = getHeight(node->rightSon);
		//有无高度变化

		if (!updateHeight(node)) break;

		if (leftHeight - rightHeight > 1) {
			Node *son = node->leftSon;
			leftHeight = getHeight(son->leftSon);
			rightHeight = getHeight(son->rightSon);
			if (leftHeight > rightHeight) {
				rightRotate(node, father);
			} else {
				leftRotate(son, node);
				rightRotate(node, father);
			}

		} else if (rightHeight - rightHeight > 1) {
			Node *son = node->rightSon;
			leftHeight = getHeight(son->leftSon);
			rightHeight = getHeight(son->rightSon);
			if (leftHeight > rightHeight) {
				rightRotate(son, node);
				leftRotate(node, father);
			} else {
				leftRotate(node, father);
			}
		}
	}
	return;
}
template<typename T>
void AVLTree<T>::leftRotate(Node *node, Node *father) {
	bool lrFlag = false;
	if (father != nullptr) {
		if (node->data < father->data) {
			father->leftSon = node->rightSon;
			Node *tmp = (node->rightSon)->leftSon;
			node->rightSon = tmp;
			(father->leftSon)->leftSon = node;
		} else {
			father->rightSon = node->rightSon;
			Node *tmp = (node->rightSon)->leftSon;
			node->rightSon = tmp;
			(father->rightSon)->leftSon = node;
			lrFlag = true;
		}
		updateHeight(node);
		(lrFlag) ? updateHeight(father->rightSon) : updateHeight(father->leftSon);
		updateHeight(father);

	} else {
		root = node->rightSon;
		node->rightSon = root->leftSon;
		root->leftSon = node;
		updateHeight(node);
		updateHeight(root);
	}
}
template<typename T>
void AVLTree<T>::rightRotate(Node *node, Node *father) {
	bool lrFlag = false;
	if (father != nullptr) {
		if (node->data < father->data) {
			father->leftSon = node->leftSon;
			Node *tmp = (node->leftSon)->rightSon;
			node->leftSon = tmp;
			(father->leftSon)->rightSon = node;
		} else {
			father->rightSon = node->leftSon;
			Node *tmp = (node->leftSon)->rightSon;
			node->leftSon = tmp;
			(father->rightSon)->rightSon = node;
			lrFlag = true;
		}
		updateHeight(node);
		(lrFlag) ? updateHeight(father->rightSon) : updateHeight(father->leftSon);
		updateHeight(father);

	} else {
		root = node->leftSon;
		node->leftSon = root->rightSon;
		root->rightSon = node;
		updateHeight(node);
		updateHeight(root);
	}
}
#endif//AVLTREE_AVLTREE_H
