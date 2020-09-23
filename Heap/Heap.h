//
// Created by 86185 on 2020/9/22.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H
#include <vector>
#include <exception>
using std::vector;
template<typename T>
class Heap{
private:
	vector<T> *heap;
	int heap_size;
	void swap(T& ra, T& rb){
		T temp = ra;
		ra = rb;
		rb = temp;
	}
public:
	Heap();
	Heap(T* begin, T* end);//连续内存的容器、数组等直接构造堆
	Heap(Heap &heap1);
	~Heap();
	void push(T value);
	void pop();
	void show_heap();
	bool empty();
	int size();
	T root();
	Heap& operator=(Heap &h){
		if(*this == h)
			return *this;
		if(heap != nullptr)
			delete heap;
		heap = new std::vector<T>(*h.heap);
	}
};
template<typename T>
Heap<T>::Heap() {
	heap = new vector<T>();
	heap_size = 0;
}
template<typename T>
Heap<T>::Heap(T* begin, T* end) {
	heap = new vector<T>();
	heap_size = 0;
	T* p = begin;
	do{
		this->push(*p);
		p++;
	}while(p!=end);
}
template<typename T>
Heap<T>::Heap(Heap &h){
	if(h == *this)
		return;
	if(heap != nullptr)
		delete heap;
	heap = new std::vector<T>(*h.heap);
}
template<typename T>
Heap<T>::~Heap() {
	delete heap;
	heap = nullptr;
}
template<typename T>
void Heap<T>::push(T value) {
	heap_size++;
	heap->push_back(value);
	int cur = heap_size - 1;
	while(cur > 0 && (*heap)[cur] > (*heap)[(cur-1)/2]){
		swap((*heap)[cur],(*heap)[(cur-1)/2]);
		cur = (cur-1)/2;
	}
}

template<typename T>
void Heap<T>::pop() {
	if(heap->empty()){
		throw "The heap is empty!";
	}
	swap((*heap)[0],(*heap)[heap_size-1]);
	heap_size--;
	heap->pop_back();
	int cur, next = 0;
	do{
		cur = next;
		int leftSon = cur*2 + 1;
		int rightSon = cur*2 + 2;
		if(leftSon < heap_size && (*heap)[cur]<(*heap)[leftSon]){
			swap((*heap)[cur],(*heap)[leftSon]);
			next = leftSon;
		}
		if(rightSon < heap_size && (*heap)[cur]<(*heap)[rightSon]){
			swap((*heap)[cur],(*heap)[rightSon]);
			next = rightSon;
		}
	}while (next != cur);
}


template<typename T>
bool Heap<T>::empty() {
	return heap->empty();
}
template<typename T>
int Heap<T>::size() {
	return heap_size;
}

template<typename T>
T Heap<T>::root() {
	return (*heap)[0];
}
#endif//HEAP_HEAP_H
