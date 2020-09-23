#include <iostream>
#include "Stack.h"
#include "Queue.h"
using std::cout;
using std::endl;
using std::string;
void test_Stack(){
	Stack<int>* stack = new Stack<int>();
	for(int i=0;i<5;i++){
		if(i!=3)
			stack->push(i);
		else stack->pop();
	}
	while(!stack->empty()){
		cout<<stack->top()<<endl;
		stack->pop();
	}
}
void test_Queue(){
	Queue<string>* queue = new Queue<string>();
	queue->pushback("Tom");
	queue->pushback("and");
	queue->pushback("Jerry");
	while(!queue->empty()){
		cout<<queue->front()<<endl;
		queue->pop();
	}
}
int main() {
	test_Stack();
	//test_Queue();

	return 0;
}
