//
// Created by 86185 on 2020/11/16.
//

#ifndef INC_2_3_TREE_2_3TREE_H
#define INC_2_3_TREE_2_3TREE_H

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;

template<typename T>
class Tree2_3 {
private:
	struct Node {
		Node *father;
		vector<T> *data;
		vector<Node *> *son;

		Node() {
			father = nullptr;
			data = new vector<T>();
			son = new vector<Node *>();
		}

		bool isLeaf() { return son->empty(); }

		bool needSplit() { return data->size() > 2; }

		void insertData(T idata) {
			if (data->empty()) {
				data->push_back(idata);
				return;
			}
			auto it = data->begin();
			for (; it != data->end() && (*it) < idata; ++it);
			data->insert(it, idata);
		}

		void deleteData(int id) {
			data->erase(data->begin() + id);
		}

		void insertSon(Node *ison) {
			son->push_back(ison);
			ison->father = this;
		}

		void deleteSon(int id) {
			son->erase(son->begin() + id);
		}

		T dataAt(int id) {
			return data->at(id);
		}

		Node *sonAt(int id) {
			return son->at(id);
		}

		int contains(T idata);

		int size() { return data->size(); }
	};

	Node *root;

	void split(Node *node);

	void merge();

	int _size(Node *fatherNode);

	int _rank(T data, Node *start); //返回rank
	void _display(Node *node);

	Node *findInsertNode(T data, Node *node) {
		if (node == nullptr)
			return nullptr;
		for (auto it = node->data->begin(); it != node->data->end(); ++it) {
			if (*it == data) return nullptr; //此data已经在树中
		}
		if (node->isLeaf()) return node;
		else {
			if (data < node->dataAt(0)) {
				return findInsertNode(data, node->sonAt(0));
			} else {
				if (node->size() > 1 && data > node->dataAt(1))
					return findInsertNode(data, node->sonAt(2));
				else
					return findInsertNode(data, node->sonAt(1));
			}
		}
	}

public:
	Tree2_3() { root = nullptr; }

	~Tree2_3() {}

	void display() { _display(root); }             //遍历
	void ins(T data);                              //插入
	void del(T data);                              //删除
	bool search(T data);                           //查找是否存在
	int rank(T data) { return _rank(data, root); } //返回rank
	int size() { return _size(root); }
};

template<typename T>
int Tree2_3<T>::Node::contains(T idata) {
	int cnt = 0;
	for (auto it = data->begin(); it != data->end(); ++it) {
		cnt++;
		if (*it == idata)
			return cnt;
	}
	return 0;
}

template<typename T>
int Tree2_3<T>::_rank(T data, Node *start) {
	if (start == nullptr)
		return 0;
	if (start->isLeaf())
		return start->contains(data);
	//左中右儿子
	if (data < start->dataAt(0)) {
		return _rank(data, start->sonAt(0));
	} else if (data == start->dataAt(0)) {
		return _size(start->sonAt(0)) + 1;
	} else if (data > start->dataAt(0)) {
		if (start->size() < 2 || data < start->dataAt(1)) {
			int rankInSon = _rank(data, start->sonAt(1));
			return rankInSon == 0 ? 0 : _size(start->sonAt(0)) + 1 + rankInSon;
		} else {
			if (data == start->dataAt(1)) {
				return _size(start->sonAt(0)) + _size(start->sonAt(1)) + 2;
			} else {
				int rankInSon = _rank(data, start->sonAt(2));
				return rankInSon == 0 ? 0 : _size(start->sonAt(0)) + _size(start->sonAt(1)) + 2 + rankInSon;
			}
		}
	}
}

template<typename T>
bool Tree2_3<T>::search(T data) {
	return rank(data) != 0;
}

template<typename T>
int Tree2_3<T>::_size(Node *fatherNode) {
	if (fatherNode == nullptr)
		return 0;
	int cnt = fatherNode->data->size();
	for (auto it = (fatherNode->son)->begin(); it != (fatherNode->son)->end(); ++it)
		cnt += _size(*it);
	return cnt;
}

template<typename T>
void Tree2_3<T>::_display(Node *node) {
	if (node->isLeaf()) {
		for (auto it = (node->data)->begin(); it != (node->data)->end(); ++it) {
			cout << *it << "  ";
		}
	} else {
		_display(node->sonAt(0));
		cout << node->dataAt(0) << "  ";
		_display(node->sonAt(1));
		if (node->size() > 1) {
			cout << node->dataAt(1) << "  ";
			_display(node->sonAt(2));
		}
	}
}

template<typename T>
void Tree2_3<T>::merge() {}

template<typename T>
void Tree2_3<T>::split(Node *node) {
	//if (node == nullptr) return;
	Node *father = node->father;
	Node *newNode = new Node();
	T midData = node->dataAt(1);
	newNode->insertData(node->dataAt(2));
	node->deleteData(2);
	node->deleteData(1);

	if (!node->isLeaf()) {
		//cout << "sizeSon:" << node->son->size() << endl;
		newNode->insertSon(node->sonAt(2));
		newNode->insertSon(node->sonAt(3));
		node->deleteSon(3);
		node->deleteSon(2);
	}

	if (father == nullptr) {
		//cout << "root==node" << (root == node) << endl;
		//根节点
		root = new Node();
		root->father = nullptr;
		root->insertSon(node), root->insertSon(newNode);
		node->father = root, newNode->father = root;
		root->insertData(midData);
	} else {
		father->insertData(midData);
		auto it = father->son->begin();
		while (*it != node) ++it;
		++it;
		father->son->insert(it, newNode);
		newNode->father = father;
		if (father->needSplit())
			split(father);
	}
}

template<typename T>
void Tree2_3<T>::ins(T data) {
	if (root == nullptr) {
		root = new Node();
		root->insertData(data);
		return;
	}
	Node *insertNode = findInsertNode(data, root);
	if (insertNode == nullptr) return;

	insertNode->insertData(data);
	if (insertNode->needSplit()) {
		split(insertNode);
	}
}

template<typename T>
void Tree2_3<T>::del(T data) {}

#endif // INC_2_3_TREE_2_3TREE_H
