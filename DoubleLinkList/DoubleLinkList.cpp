#include <iostream>
#include <cstdio>

template<typename T>
class DoubleLinkList{
	private:
	    struct Node{
		    Node* prev;
		    Node* next;
			T value;
	    };

		Node* head;
		Node* tail;
	public:
	    DoubleLinkList();
	    ~DoubleLinkList();
	    void insertNode(int index, T value);
	    void deleteNode(int index);
	    void pushNode(T value);               //在链尾插入点
	    void dropNode();                      //删除链尾的点
		void clear();                           //清空链表
		void showNode();                      //打印整张链表
	    void showNode(int l, int r);            //打印区间内的链表

	    T& getNode(int index);//获取值
	    T& back();//获取tail的值
	    T& front();//获取head的值
		int listLen();
	    bool empty(){
	            return head == nullptr;
	    };

	    //内嵌迭代器实现类的封装
	    class Iterater{
			private:
		        Node* ptr;
				DoubleLinkList<T> *list;
		    public:
		        Iterater(DoubleLinkList<T>* list, Node* p = nullptr){
			        ptr = p;
			        this->list = list;
		        }
		        ~Iterater(){
			        if(ptr != nullptr)
			            delete ptr;
		        }
		        T operator*() const{
			        return ptr->value;
		        }
		        Iterater& operator++(){ //前缀++
			        ptr = ptr->next;
			        return *this;
		        }
				Iterater& operator++(int){//后缀++
			        Iterater* old = this;
			        this->ptr = (this->ptr)->next;
			        return *old;
		        }
		        Iterater& operator--(){ //前缀--
			        ptr = ptr->prev;
			        return *this;
		        }
		        Iterater& operator--(int){//后缀--
			        Iterater* old = this;
			        this->ptr = (this->ptr)->prev;
			        return *old;
		        }
				bool operator==(const Iterater& another) const{
			        return another.ptr == this->ptr;
		        }
		        bool operator!=(const Iterater& another) const{
			        return another.ptr != this->ptr;
		        }

		        //删除节点
		        void remove(){
			        Node* prev = (this->ptr)->prev;
			        Node* next = (this->ptr)->next;
			        if(prev != nullptr)//非head
			            prev->next=next;
			        else{
				        (this->list)->head = ((this->list)->head)->next;
				        ((this->list)->head)->prev = nullptr;
			        }

			        if(next != nullptr)//非tail
				        next->prev=prev;
			        else{
				        (this->list)->tail = ((this->list)->tail)->prev;
				        ((this->list)->head)->next = nullptr;
			        }
		        }
		        //向前加节点
		        void insert(T value){
					Node* node = new Node{nullptr, nullptr, value};
			        node->prev = (this->ptr)->prev;
			        node->next = this->ptr;
			        (this->ptr)->prev = node;
			        if(this->ptr == (this->list)->head){
				        (this->list)->head = node;
			        }
		        }


		        friend std::ostream& operator<<(std::ostream & os, const Iterater& iterater)
		        {
			        os<<(iterater.ptr)->value;
			        return os;
		        }

		        //获取值
		        T& value(){
			        return (this->ptr)->value;
		        }
	    };



		Iterater begin(){
			return Iterater(this, head);
		}
		Iterater end(){
			return Iterater(this, tail->next);
		}
};


template<typename T>
DoubleLinkList<T>::DoubleLinkList() {
	head = nullptr;
	tail = nullptr;
}

template<typename T>
DoubleLinkList<T>::~DoubleLinkList() {
	clear();
}

//在指定位置插入节点
template<typename T>
void DoubleLinkList<T>::insertNode(int index, T value) {
	if(index > this->listLen()||index < 0){
		std::cout<<"The index is invalid!"<<std::endl;
		return;
	}
	if (head == nullptr || index == this->listLen()){
		pushNode(value);
		return;
	}
	Node* cur = head;
	while(index--){
		cur = cur->next;
	}
	Node* node = new Node{nullptr, nullptr, value};
	node->next = cur;
	node->prev = cur->prev;
	cur->prev = node;
	(node->prev)->next = node;
}

//删除index位置的节点
template<typename T>
void DoubleLinkList<T>::deleteNode(int index) {
	Node* cur = head;
	while(index){
		index--;
		cur = cur->next;
	}
	(cur->prev)->next = cur->next;
	(cur->next)->prev = cur->prev;
	delete cur;
}

//在链尾插入点
template<typename T>
void DoubleLinkList<T>::pushNode(T value) {
	if (head == nullptr){
		head = new Node{nullptr, nullptr, value};
		tail = head;
	}else{
		Node* node = new Node{nullptr, nullptr, value};
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
}

//删除链尾的点
template<typename T>
void DoubleLinkList<T>::dropNode() {
	if(tail == nullptr) return;
	tail = tail->prev;
	delete tail->next;
	tail->next = nullptr;
}

//清空链表
template<typename T>
void DoubleLinkList<T>::clear() {
	Node* cur = head;
	while(cur != nullptr){
		cur = cur->next;
		delete cur->prev;
	}
}

template<typename T>
void DoubleLinkList<T>::showNode() {
	Node* cur = head;
	while(cur != nullptr){
		std::cout<<cur->value<<"  ";
		cur = cur->next;
	}
	std::cout<<std::endl;
}

template<typename T>
void DoubleLinkList<T>::showNode(int l, int r){
	if(r<l){
		std::cout<<"r can't be less than l!"<<std::endl;
		return;
	}
	if(l < 0){
		std::cout<<"l is invalid!"<<std::endl;
		l = 0;
	}
	int len = this->listLen();
	if(r >= len){
		std::cout<<"r is invalid!"<<std::endl;
		r = len-1;
	}
	len = r-l+1;
	Node* cur = head;
	while(l--){
		cur = cur->next;
	}
	while(len--){
		std::cout<<cur->value<<"  ";
		cur = cur->next;
	}
}

template<typename T>
T& DoubleLinkList<T>::getNode(int index) {
	Node* cur = head;
	while(index){
		cur = cur->next;
		index--;
		if(cur == nullptr){
			std::cout<<"The index is too large! This is the last one."<<std::endl;
			return tail->value;
		}
	}
	return cur->value;
}
template<typename T>
T& DoubleLinkList<T>::back() {
	return tail->value;
}

template<typename T>
T& DoubleLinkList<T>::front() {
	return head->value;
}

template<typename T>
int DoubleLinkList<T>::listLen() {
	int len = 0;
	Node* cur = head;
	while (cur != nullptr) {
		len++;
		cur = cur->next;
	}
	return len;
}

int main() {
	DoubleLinkList<int> *doubleLinkList = new DoubleLinkList<int>();

	for(int i = 0; i < 10; i++){
		doubleLinkList->pushNode(i);
	}
	doubleLinkList->showNode();

	doubleLinkList->deleteNode(3);//删掉3位置的节点
	doubleLinkList->showNode();
	doubleLinkList->insertNode(3,3);//重新插入3节点位置的节点
	doubleLinkList->showNode();
	int result = doubleLinkList->getNode(11);//超出index范围的
	if(result != NULL){
		std::cout<<result<<std::endl;
	}
	doubleLinkList->showNode(3,5);//打印区间内节点
	std::cout<<doubleLinkList->empty();//判空
	doubleLinkList->dropNode();//删除结尾节点
	std::cout<<std::endl;

	//使用迭代器遍历和删除节点
	for(DoubleLinkList<int>::Iterater iterater = doubleLinkList->begin(); iterater != doubleLinkList->end(); iterater++){
		std::cout<<iterater<<"  ";
		if(iterater.value() == 0){
			iterater.remove();
		}
		if(iterater.value() == 1){
			iterater.insert(-1);
		}
	}
	std::cout<<std::endl;
	doubleLinkList->showNode();
	return 0;
}

