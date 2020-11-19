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
		void isLeaf() { return son->empty(); }
		void needSplit() { return data->size() > 2; }
		void insertData(T idata) { data->push_back(idata); }
		int contains(T idata);
		int size() { return data->size(); }
	};
	Node *root;
	void split(Node *node);
	void merge();
	int _size(Node *fatherNode);
	int _rank(T data, Node *start);//返回rank
	void _display(Node *node);
	Node *findeInsertNode(T data, Node *node);

public:
	Tree2_3() { root == nullptr; }
	void display() { _display(root); }            //遍历
	void ins(T data);                             //插入
	void del(T data);                             //删除
	bool search(T data);                          //查找是否存在
	int rank(T data) { return _rank(data, root); }//返回rank
	int size() { return _size(root); }
};

template<typename T>
int Tree2_3<T>::Node::contains(T idata) {
	int cnt = 0;
	for (auto it = data->begin(); it != data->end(); ++it) {
		cnt++;
		if (*it == idata) return cnt;
	}
	return 0;
}

template<typename T>
int Tree2_3<T>::_rank(T data, Node *start) {
	if (start == nullptr) return 0;
	if (start->isLeaf()) return start->contains(data);
	//左中右儿子
	if (data < *(start->data)[0]) {
		return _rank(data, *(start->son)[0]);
	} else if (data == *(start->data)[0]) {
		return _size(*(start->son)[0]) + 1;
	} else if (data > *(start->data)[0]) {
		if (start->size() < 2 || data < *(start->data)[1])
			return _size(*(start->son)[0]) + 1 + _rank(data, *(start->son)[1]);
		else {
			if (data == *(start->data)[1])
				return _size(*(start->son)[0]) + _size(*(start->son)[1]) + 2;
			else
				return _size(*(start->son)[0]) + _size(*(start->son)[1]) + 2 + _rank(data, *(start->son)[2]);
		}
	}
}

template<typename T>
bool Tree2_3<T>::search(T data) {
	return rank(data) == 0;
}

template<typename T>
int Tree2_3<T>::_size(Node *fatherNode) {
	if (fatherNode == nullptr) return 0;
	int cnt = (fatherNode->data)->size();
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
		_display(*(node->son)[0]);
		cout << *(node->data)[0] << "  ";
		_display(*(node->son)[1]);
		if (node->size() > 1) {
			cout << *(node->data)[1] << "  ";
			_display(*(node->son)[2]);
		}
	}
}

template<typename T>
typename Tree2_3<T>::Node *Tree2_3<T>::findeInsertNode(T data, Node *node) {
	if (node == nullptr) return nullptr;
	if (node->isLeaf()) {
		for (auto it = (node->data)->begin(); it != (node->data)->end(); ++it) {
			if (*it == data) return nullptr;
		}
		return node;
	}
}
template<typename T>
void Tree2_3<T>::merge() {}

template<typename T>
void Tree2_3<T>::split(Node *node) {}

template<typename T>
void Tree2_3<T>::ins(T data) {
	Node *node = findInsertNode(data, root);
}

template<typename T>
void Tree2_3<T>::del(T data) {
}


#endif//INC_2_3_TREE_2_3TREE_H
