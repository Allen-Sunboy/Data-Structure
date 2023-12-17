#include <iostream>
using namespace std; //swap()

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

    int disordered() const{
        int n = 0;
        for (int i = 1; i < _size; i++)
            if (_elem[i-1] > _elem[i])
                n++;
        return n;
    }

    int find(const T &e) const{ return find(e, 0, _size); }

    int find(const T &e, int lo, int hi) const{
        while ((lo < hi--) && (e != _elem[hi]));
        return hi;
    }

    int search(const T &e) const{ return (_size <= 0) ? -1 : search(e, 0, _size); }

    int search(const T &e, int lo, int hi) const{
        while (lo < hi)
        {
            int mi = (lo + hi) >> 1;
            (e < _elem[mi]) ? hi = mi : lo = mi + 1;
        }
        return --lo;
    }

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

    void merge(int lo, int mi, int hi){
        T *A = _elem + lo;
        int lb = mi - lo;
        T *B = new T[lb];
        for (int i = 0; i < lb; B[i] = A[i++]);
        int lc = hi - mi;
        T *C = _elem + mi;
        for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
        {
            if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))
                A[i++] = B[j++];
            if ((k < lc) && (!(j > lb) || (C[k] < B[j])))
                A[i++] = C[k++];
        }
        delete[] B;
    }

    void mergeSort(int lo, int hi){
        if (hi - lo < 2)
            return;
        int mi = (lo + hi) / 2;
        mergeSort(lo, mi);
        mergeSort(mi, hi);
        merge(lo, mi, hi);
    }

    int deduplicate(){
        int oldSize = _size;
        int i = 1;
        while (i < _size)
            (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
        return oldSize - _size;
    }

    int uniquify(){
        int i = 0, j = 0;
        while (++j < _size)
            if (_elem[i] != _elem[j])
                _elem[++i] = _elem[j];
        _size = ++i;
        shrink();
        return j - i;
    }

};

bool InHeap(int n, int i){ return -1 < i && i < n; }
int Parent(int i){ return (i - 1) >> 1; }
int LastInternal(int n){ return Parent(n - 1); }
int LChild(int i){ return 1 + (i << 1); }
int RChild(int i){ return (1 + i) << 1; }
bool ParentValid(int i){ return i; }
bool LChildValid(int n, int i){ return InHeap(n, LChild(i)); }
bool RChildValid(int n, int i){ return InHeap(n, RChild(i)); }

template <typename T>
int Bigger(T *elem, int i, int j){ return elem[i] < elem[j] ? j : i; }

template <typename T>
int ProperParent(T *elem, int n, int i){
    return RChildValid(n, i) ? Bigger(elem, Bigger(elem, i, LChild(i)), RChild(i)) :
        (LChildValid(n, i) ? Bigger(elem, i, LChild(i)) : i);
}

template <typename T>
class PQ_ComplHeap: public Vector<T>{
protected:
    int percolateDown(int n, int i){
        int j;
        while (i != (j = ProperParent(this->_elem, n, i)))
        {
            swap(this->_elem[i], this->_elem[j]);
            i = j;
        }
        return i;
    }

    int percolateUp(int i){
        while (ParentValid(i))
        {
            int j = Parent(i);
            if (this->_elem[i] < this->_elem[j])
                break;
            swap(this->_elem[i], this->_elem[j]);
            i = j;
        }
        return i;
    }

    void heapify(int n){
        for (int i = LastInternal(n); InHeap(n, i); i--)
            percolateDown(n, i);
    }

public:
    PQ_ComplHeap(){}

    PQ_ComplHeap(T *A, int n){
        this->copyFrom(A, 0, n);
        heapify(n);
    }

    void insert(T e){
        Vector<T>::insert(e);
        percolateUp(this->_size - 1);
    }

    T getMax(){ return this->_elem[0]; }

    T delMax(){
        T maxElem = this->_elem[0];
        this->_elem[0] = this->_elem[--this->_size];
        percolateDown(this->_size, 0);
        return maxElem;
    }

};

// PQ_ComplHeap<int> heap;

int main()
{

}