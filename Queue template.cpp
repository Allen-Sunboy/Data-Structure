//双向List派生
template <typename T>
struct ListNode{
    T data;
    ListNode<T> *pred;
    ListNode<T> *succ;
    ListNode(){}
    ListNode(T e, ListNode<T> *p = nullptr, ListNode<T> *s = nullptr): data(e), pred(p), succ(s){}
    ListNode<T> *insertAsPred(const T &e){
        ListNode<T> *x = new ListNode(e, pred, this);
        pred->succ = x;
        pred = x;
        return x;
    }

    ListNode<T> *insertAsSucc(const T &e){
        ListNode<T> *x = new ListNode(e, this, succ);
        succ->pred = x;
        succ = x;
        return x;
    }

};

template <typename T>
class List{
private:
    int _size;
    ListNode<T> *header;
    ListNode<T> *trailer;
    
protected:
    void init(){
        header = new ListNode<T>;
        trailer = new ListNode<T>;
        header->succ = trailer;
        header->pred = nullptr;
        trailer->pred = header;
        trailer->succ = nullptr;
        _size = 0;
    }

    int clear(){
        int oldSize = _size;
        while(_size)
            remove(header->succ);
        return oldSize;
    }

    void copyNodes(ListNode<T> *p, int n){
        init();
        while(n--)
        {
            insertAsLast(p->data);
            p = p->succ;
        }
    }

public:
    List(){ init(); }

    List(const List<T> &L){ copyNodes(L.first, L._size); }

    List(const List<T> &L, int r, int n){ copyNodes(L[r], n); }

    List(ListNode<T> *p, int n){ copyNodes(p, n); }

    ~List(){
        while(_size)
            remove(header->succ);
        delete header;
        delete trailer;
    }

    int size() const{ return _size; }

    bool empty() const{ return _size <= 0; }

    T &operator[](int r) const{
        ListNode<T> *p = first();
        while(r--)
            p = p->succ;
        return p->data;
    }

    ListNode<T> *first() const{ return header->succ; }

    ListNode<T> *last() const{ return trailer->pred; }

    bool valid(ListNode<T> *p){ return p && (trailer != p) && (header != p); }

    ListNode<T> *insertAsFirst(const T &e){
        _size++;
        return header->insertAsSucc(e);
    }

    ListNode<T> *insertAsLast(const T &e){
        _size++;
        return trailer->insertAsPred(e);
    }

    ListNode<T> *insertA(ListNode<T> *p, const T &e){
        _size++;
        return p->insertAsSucc(e);
    }

    ListNode<T> *insertB(ListNode<T> *p, const T &e){
        _size++;
        return p->insertAsPred(e);
    }

    T remove(ListNode<T> *p){
        T e = p->data;
        p->pred->succ = p->succ;
        p->succ->pred = p->pred;
        delete p;
        _size--;
        return e;
    }

};

template <typename T>
class Queue: public List<T>{
public:
    void enqueue(const T &e){ this->insertAsLast(e); }

    T dequeue(){ return this->remove(this->first()); }

    T &front(){ return this->first()->data; }

};

#include <iostream>
using namespace std;

int main()
{

}