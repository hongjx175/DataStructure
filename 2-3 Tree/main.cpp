#include "2_3Tree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

	vector<int> *vec = new vector<int>();
	vec->push_back(1);
	vec->push_back(2);
	vec->push_back(3);
	vec->erase(vec->begin() + 1);
	cout << vec->at(0) << endl;
	cout << vec->at(1) << endl;
	auto item = vec->begin();
	cout << (*item);
	vec->insert(item, 2);

	Tree2_3<int> *tree23 = new Tree2_3<int>();
	for (int i = 0; i < 10; i++)
		tree23->ins(i);
	tree23->display();
	return 0;
}
