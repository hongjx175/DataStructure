//
// Created by 86185 on 2020/9/30.
//

#ifndef CONVEX_HULL2_ALGORITHM_H
#define CONVEX_HULL2_ALGORITHM_H
#include "Stack.h"

template<typename T>
class Algorithm{
private:
	static T* middle(T *p, T *q, T *t){
		if(*p < *q && *q < *t) return q;
		if(*p < *t && *t < *q) return t;
		return p;
	}
	static T* middle(T *p, T *q, T *t, bool (*comp)(const T &a, const T &b)){
		if((*comp)(*p ,*q) && (*comp)(*q ,*t)) return q;
		if((*comp)(*p ,*t) && (*comp)(*t ,*q)) return t;
		return p;
	}
	static void swap_data(T *p, T *q){
		T temp = *p;
		*p = *q;
		*q = temp;
	}
	/*struct MyCompare{
		bool operator()(T t1, T t2){
			return t1 < t2;
		}
	}myCompare;*/
public:
	Algorithm(){};
	~Algorithm(){};

	//非递归
	static void quicksort(T *begin, T *end){
		struct range{
			T *left, *right;
		};
		Stack<range>* stack = new Stack<range>();
		stack->push(range{begin, end});
		do{
			range cur = stack->top();
			stack->pop();
			T *left = cur.left;
			T *right = cur.right;
			T mid = *(middle(left, right, left + (right - left)/2));
			while(left < right){
				while(left < right && *left < mid){
					++left;
				}
				while(left < right && mid < *right){
					--right;
				}
				swap_data(left, right);
			}
			if(cur.left < left-1) stack->push(range{cur.left, left - 1});
			if(left+1 < cur.right) stack->push(range{left + 1, cur.right});
		}while(!stack->empty());
	}

	//非递归
	static void quicksort(T *begin, T *end, bool (*comp)(const T &a, const T &b)){
		struct range{
			T *left, *right;
		};
		Stack<range>* stack = new Stack<range>();
		stack->push(range{begin, end});
		do{
			range cur = stack->top();
			stack->pop();
			T *left = cur.left;
			T *right = cur.right;
			T mid = *(middle(left, right, left + (right - left)/2, comp));
			while(left < right){
				while(left < right && (*comp)(*left, mid)){
					++left;
				}
				while(left < right && (*comp)(mid, *right)){
					--right;
				}
				swap_data(left, right);
			}
			if(cur.left < left-1) stack->push(range{cur.left, left - 1});
			if(left+1 < cur.right) stack->push(range{left + 1, cur.right});
		}while(!stack->empty());
	}


	//递归
	static void quicksort_recursive(T *begin, T *end){
		if(begin+1 > end)
			return;
		T *left = begin;
		T *right = end;
		T mid = *(middle(left, right, begin + (end - begin)/2));
		while(left < right){
			while(left < right && *left < mid){
				++left;
			}
			while(left < right && mid < *right){
				--right;
			}
			swap_data(left, right);
		}
		quicksort_recursive(begin, left-1);
		quicksort_recursive(left+1, end);
	}

	//递归
	static void quicksort_recursive(T *begin, T *end, bool (*comp)(const T &a, const T &b)){
		if(begin+1 > end)
			return;
		T *left = begin;
		T *right = end;
		T mid = *(middle(left, right, begin + (end - begin)/2, comp));
		while(left < right){
			while(left < right && (*comp)(*left, mid)){
				++left;
			}
			while(left < right && (*comp)(mid, *right)){
				--right;
			}
			swap_data(left, right);
		}
		quicksort_recursive(begin, left-1, comp);
		quicksort_recursive(left+1, end, comp);
	}
};
#endif//CONVEX_HULL2_ALGORITHM_H
