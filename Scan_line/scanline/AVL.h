#pragma once

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
template<typename T>
class AVLTree {
private:
	struct Node {
		Node* leftSon, * rightSon, * father;
		int height;
		T data;
		Node(T idata = NULL) {
			height = 1;
			leftSon = rightSon = father = nullptr;
			data = idata;
		}
		friend ostream& operator<<(ostream&, Node& node) {
			cout << node.data;
			return cout;
		}
	};
	Node* root;
	//void leftRotate(Node *node);
	//void rightRotate(Node *node);
	void balance(Node* node, bool lrFlag);
	int max(int a, int b) { return a > b ? a : b; }
	int getHeight(Node* node) { return node == nullptr ? 0 : node->height; }
	bool updateHeight(Node* node);
	void update(Node* node);
	void _display(Node* node);

public:
	AVLTree() { root = nullptr; }
	~AVLTree() {
		while (root)
			del(root->data);
	}
	void ins(T data);
	void del(T data);
	void display();
	int height() { return getHeight(root); };
};
template<typename T>
bool AVLTree<T>::updateHeight(Node* node) {
	if (node == nullptr) return false;
	int height = getHeight(node);
	node->height = max(getHeight(node->leftSon), getHeight(node->rightSon)) + 1;
	if (height < node->height) return true;
	return false;
}
template<typename T>
void AVLTree<T>::balance(Node* node, bool lrFlag) {
	Node* father = node->father, * son = (lrFlag) ? node->leftSon : node->rightSon;//lrFlagÎªÕæÓÒÐý
	if (father != nullptr) {
		if (node == father->leftSon)//×ó¶ù×Ó
			father->leftSon = son;
		else//ÓÒ¶ù×Ó
			father->rightSon = son;
	}
	else {
		root = son;
	}
	if (node) (lrFlag) ? (node->leftSon = son->rightSon) : (node->rightSon = son->leftSon);
	if (son) (lrFlag) ? (son->rightSon = node) : (son->leftSon = node);
	if (lrFlag) {
		if (node->leftSon) (node->leftSon)->father = node;
	}
	else {
		if (node->rightSon) (node->rightSon)->father = node;
	}

	if (node) node->father = son;
	if (son) son->father = father;

	updateHeight(node);
	updateHeight(son);
	updateHeight(father);
}
template<typename T>
void AVLTree<T>::update(Node* node) {
	while (node != nullptr) {
		if (getHeight(node->leftSon) - getHeight(node->rightSon) > 1) {
			Node* son = node->leftSon;
			if (getHeight(son->leftSon) >= getHeight(son->rightSon)) {
				balance(node, true);//rightRotate(node);
			}
			else {
				balance(son, false);//leftRotate(son);
				balance(node, true);//rightRotate(node);
			}
		}
		else if (getHeight(node->rightSon) - getHeight(node->leftSon) > 1) {
			Node* son = node->rightSon;
			if (getHeight(son->leftSon) > getHeight(son->rightSon)) {
				balance(son, true);  //rightRotate(son);
				balance(node, false);//leftRotate(node);
			}
			else {
				balance(node, false);//leftRotate(node);
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
	Node* newNode = new Node(data);
	Node* node = root;
	while (node != nullptr) {
		if (data < node->data) {
			if (node->leftSon != nullptr) {
				node = node->leftSon;
			}
			else {
				newNode->father = node;
				node->leftSon = newNode;
				update(node);
				break;
			}
		}
		else {
			if (node->rightSon != nullptr) {
				node = node->rightSon;
			}
			else {
				newNode->father = node;
				node->rightSon = newNode;
				update(node);
				break;
			}
		}
	}
}
template<typename T>
void AVLTree<T>::del(T data) {
	Node* node = root;
	while (node != nullptr) {
		if (data == node->data) {
			if (node == root && node->leftSon == nullptr) {
				root = node->rightSon;
				break;
			}
			Node* node1 = node;
			while (node1->leftSon) {
				node1 = node1->leftSon;
				while (node1->rightSon) node1 = node1->rightSon;
				node->data = node1->data;
				node = node1;
			}
			(node->father)->leftSon == node ? (node->father)->leftSon = nullptr : (node->father)->rightSon = nullptr;
			delete node;
			update(node->father);
			break;
		}
		node = (data < node->data) ? node->leftSon : node->rightSon;
		if (!node) cout << "Invalid Data!" << endl;
	}
	return;
}
template<typename T>
void AVLTree<T>::display() {
	_display(root);
	cout << endl;
}
template<typename T>
void AVLTree<T>::_display(Node* node) {
	(node->leftSon != nullptr) ? _display(node->leftSon) : void();
	//cout << node->height << "  " << getHeight(node->leftSon) << "  " << getHeight(node->rightSon) << endl;
	cout << *node << "  ";
	(node->rightSon != nullptr) ? _display(node->rightSon) : void();
}

/*
template<typename T>
void AVLTree<T>::leftRotate(Node *node) {
	Node *father = node->father, *son = node->rightSon;
	if (father != nullptr) {
		if (node == father->leftSon)//×ó¶ù×Ó
			father->leftSon = son;
		else//ÓÒ¶ù×Ó
			father->rightSon = son;
	} else {
		root = son;
	}

	if (node) node->rightSon = son->leftSon;
	if (son) son->leftSon = node;
	if (node->rightSon) (node->rightSon)->father = node;
	if (node) node->father = son;
	if (son) son->father = father;

	updateHeight(node);
	updateHeight(son);
	updateHeight(father);
}
template<typename T>
void AVLTree<T>::rightRotate(Node *node) {
	Node *father = node->father, *son = node->leftSon;
	if (father != nullptr) {
		if (node == father->leftSon)
			father->leftSon = son;
		else
			father->rightSon = son;
	} else {
		root = son;
	}

	if (node) node->leftSon = son->rightSon;
	if (son) son->rightSon = node;
	if (node->leftSon) (node->leftSon)->father = node;
	if (node) node->father = son;
	if (son) son->father = father;

	updateHeight(node);
	updateHeight(son);
	updateHeight(father);
}*/