#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::swap;
int n;
void getAllPermutation(int len){
	cout<<"all permutations of "<<n<<" elements"<<endl;
	int permutation[n+1];
	int orient[n+1];
	for(int i=1;i<=n;i++) {
		permutation[i] = i;
		orient[i] = -1;//朝左
	}
	cout<<endl;
	do{
		for(int i=1;i<=n;i++) cout<<permutation[i]<<" ";
		cout<<endl;
		int pos = -1, maxn = 1;
		for(int i=1;i<=n;i++){
			if(permutation[i]>maxn && i+orient[i] <= n && i+orient[i]>=1 && permutation[i+orient[i]] < permutation[i]){
				pos = i;
				maxn = permutation[i];
			}
		}
		if(pos == -1) break;
		swap(permutation[pos], permutation[pos+orient[pos]]);
		swap(orient[pos], orient[pos+orient[pos]]);
		for(int i=1;i<=n;i++)
			if(permutation[i] > maxn)
				orient[i] *= -1;
	}while (true);
}
void getPermutation(int rank){
	int permutation[n+1], cnt=0;
	for(int i=1;i<=n;i++) permutation[i] = 0;

}
void getRank(int permutation[]){

}
int main() {
	int rank;
	cout<<"Please enter the length of the permutation"<<endl;
	cin>>n;
	getAllPermutation(n);
	cout<<"请输入一个次序"<<endl;
	cin>>rank;
	getPermutation(rank);
	cout<<"请输入一个排列"<<endl;
	int permutation[n+1];
	for(int i=1;i<=n;i++){
		cin>>permutation[i];
	}
	getRank(permutation);
	return 0;
}
