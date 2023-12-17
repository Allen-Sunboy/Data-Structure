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
            if (child + 1 < this->_size && this->_data[child + 1] > this->_data[child])
                child++;
            if (this->_data[i] > this->_data[child])
                break;
            swap(this->_data[i], this->_data[child]);
            i = child;
        }

    }

    void percolateUp(int i) {
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (this->_data[i] > this->_data[parent])
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

    T getMax(){ return this->_data[0]; }

    void delMax(){
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

int main()
{

}