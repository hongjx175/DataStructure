//
// Created by 86185 on 2020/10/26.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H
template<typename T>
class AVLTree {
private:
	struct Node {
		Node *leftSon, *rightSon;
		int height;
		T data;
		Node() {
			height = 0;
			leftSon = rightSon = nullptr;
		}
	};
	Node *root;

public:
	AVLTree() {
		root = nullptr;
	}
	~AVLTree() {
	}
	void ins(T data);
};
template<typename T>
void AVLTree<T>::ins(T data) {
}
#endif//AVLTREE_AVLTREE_H
