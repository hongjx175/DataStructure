//
// Created by 86185 on 2020/9/15.
//

#ifndef STACK_QUEUE_QUEUE_H
#define STACK_QUEUE_QUEUE_H

#include "DoubleLinkedList.h"

template<typename T>
class Queue{
private:
	DoubleLinkList<T>* list;

public:
	Queue(){
		list = new DoubleLinkList<T>();
	}
	~Queue(){
		delete list;
	}
	bool empty(){
		return list->empty();
	}
	T& front(){
		if(!list->empty()){
			return list->front();
		}
		else{
			//return NULL;
		}
	}
	T& back(){
		if(!list->empty()){
			return list->back();
		}
		else{
			//return NULL;
		}
	}
	void pushback(T value){
		list->pushNode(value);
	}
	void pop(){
		list->deleteNode(0);
	}
	int size(){
		return list->listLen();
	}
};


#endif//STACK_QUEUE_QUEUE_H
