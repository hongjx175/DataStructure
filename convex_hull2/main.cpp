#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Stack.h"
#include "Algorithm.h"
#include<fstream>
#define random() (rand()%2001-1000)

using std::endl;
using std::cout;
using std::sort;
using std::ofstream;
using std::string;
struct Node{
	int x, y;
};
Node* root;
void swap(Node *pNode1, Node *pNode2) {
	Node temp = *pNode1;
	*pNode1 = *pNode2;
	*pNode2 = temp;
}

bool point_comp(const Node &a,const Node &b)
{
	double A = atan2(a.y - root->y,a.x - root->x);
	double B = atan2(b.y - root->y,b.x - root->x);
	if(A != B) return A < B;
	else return a.x<b.x;
}
int cross(const Node &a, const Node &b, const Node &c){
	return ((a.x-c.x) * (b.y-c.y) - (b.x-c.x) * (a.y-c.y));
}
int main() {
	ofstream f("../points.txt");
	f.clear();
	unsigned seed = time(0);
	srand(seed);
	int num = (rand()%31) + 30;
	Node nodes[num];
	Stack<Node>* stack = new Stack<Node>();
	for(int i=0;i<num;i++){
		nodes[i] = Node{random(),random()};
		if(i != 0){
			if(nodes[i].y < nodes[0].y || (nodes[i].y == nodes[0].y && nodes[i].x < nodes[0].x))
				swap(&nodes[i], &nodes[0]);
		}
	}

	root = &nodes[0];
	Algorithm<Node>* al = new Algorithm<Node>;
	al->quicksort(nodes+1, nodes+num-1, point_comp);
	f<<num<<endl;
	for(int i=0;i<num;i++){
		f<<nodes[i].x<<endl<<nodes[i].y<<endl;
	}


	stack->push(nodes[0]);
	stack->push(nodes[1]);

	for(int i=2;i<num;){
		Node before,tmp;
		tmp = stack->top();
		stack->pop();
		before = stack->top();
		stack->push(tmp);
		if((stack->deep() >= 2) && (cross(nodes[i], stack->top(), before) >= 0)){
			stack->pop();
		}
		else
			stack->push(nodes[i++]);
	}

	f<<stack->deep()+1<<endl;
	f<<root->x<<endl<<root->y<<endl;
	while(!stack->empty()){
		Node node = (stack->top());
		f<<node.x<<endl<<node.y<<endl;
		stack->pop();
	}

	return 0;
}

