#include <iostream>
#include "Algorithm.h"
using std::cout;
using std::endl;
bool comp(const int &a,const int &b){
	return a>b;
}

int main() {

	int a[] = {5,6,0,1,9};
	Algorithm<int>* al = new Algorithm<int>();
	al->quicksort_recursive(a+0,a+4);
	cout<<"quicksort_recursive"<<endl;
	for(int i=0;i<5;i++){
		cout<<a[i]<<endl;
	}
	cout<<"quicksort_recursive with comp func"<<endl;
	al->quicksort_recursive(a+0,a+4, comp);
	for(int i=0;i<5;i++){
		cout<<a[i]<<endl;
	}

	cout<<"quicksort"<<endl;
	al->quicksort(a+0,a+4);
	for(int i=0;i<5;i++){
		cout<<a[i]<<endl;
	}
	cout<<"quicksort with comp func"<<endl;
	al->quicksort(a+0,a+4, comp);
	for(int i=0;i<5;i++){
		cout<<a[i]<<endl;
	}
	return 0;
}
