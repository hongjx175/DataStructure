#include <iostream>
#include "Heap.h"
using std::cout;
using std::endl;

int main() {
	Heap<int>* heap = new Heap<int>();

	heap->push(5);
	heap->push(3);
	heap->push(4);
	heap->push(1);
	heap->push(2);

	while(!heap->empty()){
		cout<<heap->root()<<endl;
		heap->pop();
	}
	int a[] = {5,3,4,1,2};
	Heap<int>* heap1 = new Heap<int>(a+0,a+5);
	while(!heap1->empty()){
		cout<<heap1->root()<<endl;
		heap1->pop();
	}
	return 0;
}
