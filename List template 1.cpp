//单向，有表头结点，对外不可见，从表头编号为0开始往后编号
template <class T>
struct ListNode{
    T data;
    ListNode *next;
    ListNode(){}
    ListNode(T x){ data = x; }

};

template <class T>
class List{
private:
    //表头结点
    ListNode<T> *first;
    int _size = 0;

public:
    List(){ first = new ListNode<T>; }

    //i=0时为表头结点
    ListNode<T> *locate(int i){
        if(i < 0 || i > _size)
            return nullptr;
        ListNode<T> *current = first;
        int k = 0;
        while(k < i)
        {
            current = current->next;
            k++;
        }
        return current;
    }

    bool insert(int i, const T &x){
        ListNode<T> *current = locate(i);
        if(current == nullptr)
            return false;
        ListNode<T> *newNode = new ListNode<T>(x);
        newNode->next = current->next;
        current->next = newNode;
        _size++;
        return true;
    }

    bool remove(int i, const T &x){
        ListNode<T> *current = locate(i-1);
        if(current == nullptr)
            return false;
        ListNode<T> *del = current->next;
        current->next = del->next;
        x = del->data;
        delete del;
        _size--;
        return true;
    }

    int size(){ return _size; }

};

#include <iostream>
using namespace std;


int main()
{
    
}