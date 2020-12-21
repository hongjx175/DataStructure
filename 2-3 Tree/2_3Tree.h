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
using std::swap;

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

		int size() { return data->size(); }//用于判断是2节点还是3节点
	};

	Node *root;

	//void swap(Node *node1, Node *node2);
	void split(Node *node);

	void merge();

	int _size(Node *fatherNode);//子树size

	int _rank(T data, Node *start); //返回rank
	void _display(Node *node);

	void _del(Node *node);

	Node *findInsertNode(T data, Node *node) {
		if (node == nullptr) return nullptr;
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

	Node *findDeleteNode(T data, Node *node) {
		if (node == nullptr) return nullptr;
		for (auto it = node->data->begin(); it != node->data->end(); ++it) {
			if (*it == data) return node; //此data在树中
		}

		if (data < node->dataAt(0)) {
			return findDeleteNode(data, node->sonAt(0));
		} else {
			if (node->size() > 1 && data > node->dataAt(1))
				return findDeleteNode(data, node->sonAt(2));
			else
				return findDeleteNode(data, node->sonAt(1));
		}
	}

	Node *findNextNode(T data, Node *node) {
		Node *nextNode = nullptr;
		if (data == node->dataAt(0)) nextNode = node->sonAt(1);
		if (data == node->dataAt(1)) nextNode = node->sonAt(2);
		while (!nextNode->isLeaf()) nextNode = nextNode->sonAt(0);
		return nextNode;
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
void Tree2_3<T>::_del(Node *node) {}

template<typename T>
void Tree2_3<T>::del(T data) {
	Node *deleteNode = findDeleteNode(data, root);
	if (deleteNode == nullptr) return;

	//删除非叶子节点，转化成删除后继（必为叶子节点）
	if (!deleteNode->isLeaf()) {
		Node *nextNode = findNextNode(data, deleteNode);
		for (auto it = deleteNode->data->begin(); it != deleteNode->data->end(); ++it) {
			if (*it == data) {
				*it = nextNode->dataAt(0);
				*(nextNode->data->begin()) = data;
				break;
			}
		}
		deleteNode = nextNode;
	}

	auto deletePosition = deleteNode->data->begin();
	while (*deletePosition != data) ++deletePosition;

	if (deleteNode->size() > 1) {
		//本身是3节点（叶节点，直接删除）
		deleteNode->data->erase(deletePosition);
	} else {
		Node *father = deleteNode->father;

		//本身是2节点，父亲是2节点
		if (father->size() == 1) {
			Node *brother = father->sonAt(0);
			if (brother == deleteNode) brother = father->sonAt(1);

			//本身是2节点，父亲是2节点且兄弟是3节点
			if (brother->size() == 2) {
				deleteNode->data->erase(deletePosition);
				deleteNode->insertData(father->dataAt(0));
				father->deleteData(0);
				//本身是左儿子  /   右儿子
				if (deleteNode == father->sonAt(0)) {
					father->insertData(brother->dataAt(0));
					brother->deleteData(0);
				} else {
					father->insertData(brother->dataAt(1));
					brother->deleteData(1);
				}
			} //本身是2节点，父亲是2节点且兄弟是2节点
			else {

			}
		} //本身是2节点，父亲是3节点
		else {
			//是否有3节点兄弟
			bool has3brother =
					(father->sonAt(0)->size() > 1) || (father->sonAt(1)->size() > 1) || (father->sonAt(2)->size() > 1);

			//有 / 无 3节点兄弟
			//本身是2节点，父亲是3节点，有3节点兄弟
			if (has3brother) {
				Node *brother2, *brother3;
				if (deleteNode) {

				}
			} //无3节点兄弟
			else {
				//要删除的点为左儿子
				if (deleteNode == father->sonAt(0)) {
					father->deleteSon(0);
					father->sonAt(0)->insertData(father->dataAt(0));
					father->deleteData(0);
				}//要删除的点为中、右儿子
				else {
					if (deleteNode == father->sonAt(1)) father->deleteSon(1);
					else father->deleteSon(2);
					father->sonAt(1)->insertData(father->dataAt(1));
					father->deleteData(1);
				}
			}
		}
	}
}

#endif // INC_2_3_TREE_2_3TREE_H
