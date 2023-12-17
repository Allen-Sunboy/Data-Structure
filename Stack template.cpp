const int DEFAULT_CAPACITY = 3;
template <typename T>
class Vector{
protected:
    int _size;
    int _capacity;
    T* _elem;

    void copyFrom(const T *A, int lo, int hi){
        _elem = new T[_capacity = 2 * (hi - lo)];
        _size = 0;
        while (lo < hi)
            _elem[_size++] = A[lo++];
    }

    void expand(){
        if (_size < _capacity)
            return;
        if (_capacity < DEFAULT_CAPACITY)
            _capacity = DEFAULT_CAPACITY;
        T *oldElem = _elem;
        _elem = new T[_capacity <<= 1];
        for (int i = 0; i < _size; i++)
            _elem[i] = oldElem[i];
        delete[] oldElem;
    }

    void shrink(){
        if (_capacity < DEFAULT_CAPACITY << 1)
            return;
        if (_size << 2 > _capacity)
            return;
        T *oldElem = _elem;
        _elem = new T[_capacity >>= 1];
        for (int i = 0; i < _size; i++)
            _elem[i] = oldElem[i];
        delete[] oldElem;
    }

public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = {}){ //注意这里T v的初始化，课本写的是=0，不普适
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }

    Vector(const T *A, int n){ copyFrom(A, 0, n); }

    Vector(const T *A, int lo, int hi){ copyFrom(A, lo, hi); }

    Vector(const Vector<T> &V){ copyFrom(V._elem, 0, V._size); }

    Vector(const Vector<T> &V, int lo, int hi){ copyFrom(V._elem, lo, hi); }

    ~Vector(){ delete[] _elem; }

    int size() const{ return _size; }

    bool empty() const{ return !_size; }

    T &operator[](int r) const{ return _elem[r]; }

    Vector<T> &operator=(const Vector<T> &V){
        if (_elem)
            delete[] _elem;
        copyFrom(V._elem, 0, V._size);
        return *this;
    }

    T remove(int r){
        T e = _elem[r];
        remove(r, r+1);
        return e;
    }

    int remove(int lo, int hi){
        if (lo == hi)
            return 0;
        while (hi < _size)
            _elem[lo++] = _elem[hi++];
        _size = lo;
        shrink();
        return hi - lo;
    }

    int insert(int r, const T &e){
        expand();
        for (int i = _size; i > r; --i)
            _elem[i] = _elem[i-1];
        _elem[r] = e;
        ++_size;
        return r;
    }

    int insert(const T &e){ return insert(_size, e); }

};

template <typename T>
class Stack: public Vector<T>{
public:
    void push(const T &e){ this->insert(this->size(), e); }

    T pop(){ return remove(this->size() - 1); }

    T &top(){ return (*this)[this->size() - 1]; }

};

#include <iostream>
using namespace std;

int main()
{
    
}