#include <iostream>
using namespace std; //swap()

template <typename T>
class Vector{
protected:
    int _size = 0;
    int _capacity = 3;
    T* _data;

public:
    Vector(): _size(0), _capacity(0), _data(nullptr){}

    Vector(T *A, int n){
        this->_data = new T[n];
        for (int i = 0; i < n; i++)
            this->_data[i] = A[i];
        this->_size = n;
        this->_capacity = n;
    }

    ~Vector(){ delete[] _data; }

    void insert(T element) { insert(this->_size, element); }

    void insert(int index, T element){
        if (index < 0 || index > _size)
            return;
        
        if (_size == _capacity)
        {
            _capacity *= 2;
            T* new_data = new T[_capacity];
            for (int i = 0; i < _size; i++)
                new_data[i] = move(_data[i]);
            delete[] _data;
            _data = new_data;
        }
        _data[_size] = element;
        _size++;
    }

    void remove(int index){
        if (index < 0 || index >= _size)
            return;
        for (int i = index; i < _size - 1; i++)
            _data[i] = _data[i + 1];
        _size--;
    }

    int size(){ return _size; }

};

template <typename T>
class Heap : public Vector<T>{
public:
    Heap(){}

    Heap(T *A, int n): Vector<T>(A, n){ heapify(); }

    void percolateDown(int i){
        while (i * 2 + 1 < this->_size)
        {
            int child = i * 2 + 1;
            if (child + 1 < this->_size && this->_data[child + 1] < this->_data[child])
                child++;
            if (this->_data[i] < this->_data[child])
                break;
            swap(this->_data[i], this->_data[child]);
            i = child;
        }

    }

    void percolateUp(int i) {
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (this->_data[i] < this->_data[parent])
            {
                swap(this->_data[i], this->_data[parent]);
                i = parent;
            }
            else
                break;
        }
    }

    void heapify(){
        for (int i = this->_size / 2 - 1; i >= 0; i--)
            percolateDown(i);
    }

    T getMin(){ return this->_data[0]; }

    void delMin(){
        if (this->_size == 0)
            return;
        swap(this->_data[0], this->_data[this->_size - 1]);
        this->_size--;
        percolateDown(0);
    }

    void insert(T A)
    {
        this->Vector<T>::insert(A);
        percolateUp(this->_size - 1);
    }

};

#include <cstring> //strcmp()

const int MAXN = 4000007;

struct task{
    long long priority;
    char name[10];
};
task t[MAXN];

bool operator<(const task &T1, const task &T2)
{
    if (T1.priority < T2.priority)
        return true;
    else if (T1.priority == T2.priority && strcmp(T1.name, T2.name) < 0)
        return true;
    else
        return false;
}

int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        scanf("%lld%s", &t[i].priority, t[i].name);

    Heap<task> h(t, n);

    for (int i = 0; i < m; i++)
    {
        if (h.size() > 0)
        {
            task tmp = h.getMin();
            h.delMin();
            printf("%s\n", tmp.name);
            tmp.priority *= 2;
            if (tmp.priority < 4294967296) //2^32
                h.insert(tmp);
        }
    }
}