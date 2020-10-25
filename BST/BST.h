//
// Created by 86185 on 2020/10/21.
//

#ifndef BST_BST_H
#define BST_BST_H
#include "DoubleLinkedList.h"
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
template<typename T>
class BST {
private:
	struct Node {
		T data;
		Node *leftSon, *rightSon;
		bool leftFlag, rightFlag;
		Node() {
			data = NULL;
			leftSon = rightSon = nullptr;
			leftFlag = rightFlag = false;
		}
		Node(T &idata) {
			data = idata;
			leftSon = rightSon = nullptr;
			leftFlag = rightFlag = false;
		}
		friend ostream &operator<<(ostream &, Node &node) {
			cout << node.data;
			return cout;
		}
	};
	Node *root;
	DoubleLinkList<Node *> *list;

public:
	BST() {
		root = nullptr;
		list = new DoubleLinkList<Node *>();
	};
	~BST() {
		delete[] root;
	};
	void ins(T data);
	void del(T data);
	void del(Node *node);
	T getData(int kth);
	void display();
};
template<typename T>
void BST<T>::ins(T data) {
	if (root == nullptr) {
		root = new Node(data);
		return;
	}
	Node *node = root;
	Node *newNode = new Node(data);
	while (node != nullptr) {
		if (data < node->data) {
			if (node->leftFlag) {
				node = node->leftSon;
			} else {
				newNode->leftSon = node->leftSon;
				newNode->rightSon = node;
				node->leftSon = newNode;
				node->leftFlag = true;
				break;
			}
		} else {
			if (node->rightFlag) {
				node = node->rightSon;
			} else {
				newNode->rightSon = node->rightSon;
				newNode->leftSon = node;
				node->rightSon = newNode;
				node->rightFlag = true;
				break;
			}
		}
	}
}
template<typename T>
void BST<T>::del(T data) {
	if (root == nullptr) {
		cout << "Empty Tree!" << endl;
		return;
	}
	Node *node = root;
	//找到节点
	while (node != nullptr) {
		if (data < node->data) {
			if (node->leftFlag)
				node = node->leftSon;
			else {
				cout << "Invalid Data!" << endl;
				return;
			}
		} else if (data > node->data) {
			if (node->rightFlag)
				node = node->rightSon;
			else {
				cout << "Invalid Data!" << endl;
				return;
			}
		}
		if (node->data == data) break;
	}
	del(node);
}
template<typename T>
void BST<T>::del(Node *node) {
	Node *node1 = node, *node1Father = nullptr;
	if (node1->leftFlag) {
		node1Father = node1;
		node1 = node1->leftSon;
		while (node1 != nullptr && node1->rightFlag) {
			node1Father = node1;
			node1 = node1->rightSon;
		}
	}
	if (node1 == node) {
		//一定无左儿子
		//删除node，两种情况，node为其父节点的左/右儿子
		if ((node->rightSon)->leftSon == node) {
			Node *father = node->rightSon;
			father->leftSon = node->leftSon;
			father->leftFlag = false;
			delete node;
			node = nullptr;
		} else {
			Node *father = node->leftSon;
			father->rightSon = node->rightSon;
			father->rightFlag = node->rightFlag;
			delete node;
			node = nullptr;
		}
	} else {
		node->data = node1->data;
		del(node1);
	}
	return;
}
template<typename T>
T BST<T>::getData(int kth) {
	if (root == nullptr) {
		cout << "Empty Tree!" << endl;
		return NULL;
	}
	if (kth < 1) {
		cout << "Invalid Index!" << endl;
		return NULL;
	}

	Node *node = root;
	while (node->leftFlag) {
		node = node->leftSon;
	}
	while (node != nullptr && kth > 1) {
		if (node->rightFlag) {
			node = node->rightSon, kth--;
			while (node->leftFlag) node = node->leftSon;
		} else {
			node = node->rightSon, kth--;
		}
	}
	if (node == nullptr) throw "Invalid Index!";
	return node->data;
}
template<typename T>
void BST<T>::display() {
	if (root == nullptr) {
		cout << "Empty Tree!" << endl;
		return;
	}
	Node *node = root;
	while (node->leftFlag) {
		node = node->leftSon;
	}
	while (node != nullptr) {
		cout << *node << "  ";
		if (node->rightFlag) {
			node = node->rightSon;
			while (node->leftFlag) {
				node = node->leftSon;
			}
		} else {
			node = node->rightSon;
		}
	}
	cout << endl;
}
#endif//BST_BST_H
