#include <iostream>
using std::cout;
using std::endl;
using std::cin;
int n;
void getAllPermutation(int len){

}
void getPermutation(int rank){

}
void getRank(int permutation[]){

}
int main() {
	int rank;
	cout<<"请输入一个次序"<<endl;
	cin>>rank;
	getPermutation(rank);
	cout<<"请输入排列长度"<<endl;
	cin>>n;
	cout<<"请输入一个排列"<<endl;
	int permutation[n+1];
	for(int i=1;i<=n;i++){
		cin>>permutation[i];
	}
	getRank(permutation);
	cout<<n<<"个数的全排列"<<endl;
	return 0;
}
