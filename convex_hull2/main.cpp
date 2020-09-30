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
using std::vector;
struct Node{
	int x, y;
};
void swap(Node *pNode1, Node *pNode2) {
	Node temp = *pNode1;
	*pNode1 = *pNode2;
	*pNode2 = temp;
}

bool point_comp(const Node &a,const Node &b)
{
	if(a.x == b.x) return a.y<b.y;
	else return a.x<b.x;
}
int cross(const Node &a, const Node &b, const Node &c){
	return ((a.x-c.x) * (b.y-c.y) - (b.x-c.x) * (a.y-c.y));
}

vector<Node> getConv(vector<Node> nodes){
	//cout<<"1"<<endl;
	vector<Node> conv;
	/*if(nodes.size() < 3){
		conv = nodes;
		return conv;
	}
	if(nodes.size() == 3){
		conv.push_back(nodes[0]);
		//逆时针
		if(cross(nodes[1],nodes[2],nodes[0]) < 0){
			swap(&nodes[1], &nodes[2]);
		}
		conv.push_back(nodes[1]);
		conv.push_back(nodes[2]);
		return conv;
	}*/
	if(nodes.size() <= 7){
		int size = nodes.size();
		int root = 0;
		for(int i=0;i<size;i++){
			root = (nodes[i].x<nodes[root].x || (nodes[i].x==nodes[root].x&&nodes[i].y<nodes[root].y))?i:root;
		}
		for(int i=0;i<size;i++){


		}
	}

	vector<Node> left(nodes.begin()+0,nodes.begin()+nodes.size()/2);
	vector<Node> right(nodes.begin()+nodes.size()/2, nodes.end());
	vector<Node> left_conv = getConv(left);
	vector<Node> right_conv = getConv(right);


	//合并
	int ra = 0, lb = 0, sizeA = left_conv.size(), sizeB = right_conv.size();
	int uppera, lowera, upperb, lowerb;
	for(int i = 0; i < sizeA; i++){
		if(left_conv[i].x > left_conv[ra].x)
			ra = i;
	}
	for(int i = 0; i < sizeB; i++){
		if(right_conv[i].x < right_conv[lb].x)
			lb = i;
	}

	//下公切线
	int a = ra, b = lb;
	while(cross(left_conv[a], left_conv[(a-1+sizeA)%sizeA], right_conv[b]) >= 0
	       || cross(right_conv[b], right_conv[(b+1)%sizeB], left_conv[a]) <= 0){
		while(cross(left_conv[a], left_conv[(a-1+sizeA)%sizeA], right_conv[b]) >= 0){
			a = (a - 1+sizeA)%sizeA;
		}
		while(cross(right_conv[b], right_conv[(b+1)%sizeB], left_conv[a]) <= 0){
			b = (b + 1 )%sizeB;
		}
	}
	lowera = a;
	lowerb = b;

	//上公切线
	a = ra, b = lb;
	while(cross(left_conv[a], left_conv[(a+1)%sizeA], right_conv[b]) <= 0
	      || cross(right_conv[b], right_conv[(b-1+sizeB)%sizeB], left_conv[a]) >= 0){
		while(cross(left_conv[a], left_conv[(a+1)%sizeA], right_conv[b]) <= 0){
			a = (a + 1)%sizeA;
		}
		while(cross(right_conv[b], right_conv[(b-1+sizeB)%sizeB], left_conv[a]) >= 0){
			b = (b - 1 + sizeB)%sizeB;
		}
	}
	uppera = a;
	upperb = b;

	//合并
	a = uppera;
	while(a != lowera){
		conv.push_back(left_conv[a]);
		a = (a + 1)%sizeA;
	}
	b = lowerb;
	while(b != upperb){
		conv.push_back(right_conv[b]);
		b = (b + 1)%sizeB;
	}
	return conv;
}

int main() {
	ofstream f("../points.txt");
	f.clear();
	unsigned seed = time(0);
	srand(seed);
	int num = (rand()%31) + 30;
	vector<Node> nodes;
	for(int i=0;i<num;i++){
		nodes.push_back(Node{random(),random()});
		if(i != 0){
			if(nodes[i].y < nodes[0].y || (nodes[i].y == nodes[0].y && nodes[i].x < nodes[0].x))
				swap(&nodes[i], &nodes[0]);
		}
	}

	Algorithm<Node>* al = new Algorithm<Node>;
	al->quicksort(&nodes[0], &nodes[num-1], point_comp);
	f<<num<<endl;
	for(int i=0;i<num;i++){
		f<<nodes[i].x<<endl<<nodes[i].y<<endl;
		//cout<<nodes[i].x<<"  "<<nodes[i].y<<endl;
	}
	vector<Node> conv = getConv(nodes);
	int size = conv.size();
	f<<size+1<<endl;
	for(int i=0;i<size;i++){
		f<<conv[i].x<<endl<<conv[i].y<<endl;
	}
	f<<conv[0].x<<endl<<conv[0].y<<endl;
	return 0;
}

