//
// Created by 86185 on 2020/9/15->
//

#ifndef STACK_QUEUE_STACK_H
#define STACK_QUEUE_STACK_H

#include "DoubleLinkedList.h"
template<typename T>
class Stack{
private:
	DoubleLinkList<T>* list;

public:
	Stack(){
		list = new DoubleLinkList<T>();
	}
	~Stack(){
		delete list;
	}
	void pop(){
		list->dropNode();
	}
	void push(T value){
		list->pushNode(value);
	}
	T& top(){
		return list->back();
	}
	bool empty(){
		return list->empty();
	}
	int deep(){
		return list->listLen();
	}
};

#endif//STACK_QUEUE_STACK_H
