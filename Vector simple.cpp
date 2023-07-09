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
        for(int i = 0; i < n; i++)
            this->_data[i] = A[i];
        this->_size = n;
        this->_capacity = n;
    }

    ~Vector(){ delete[] _data; }

    void insert(T element) { insert(this->_size, element); }

    void insert(int index, T element){
        if(index < 0 || index > _size)
            return;
        
        if(_size == _capacity)
        {
            _capacity *= 2;
            T* new_data = new T[_capacity];
            for(int i = 0; i < _size; i++)
                new_data[i] = move(_data[i]);
            delete[] _data;
            _data = new_data;
        }
        _data[_size] = element;
        _size++;
    }

    void remove(int index){
        if(index < 0 || index >= _size)
            return;
        for(int i = index; i < _size - 1; i++)
            _data[i] = _data[i + 1];
        _size--;
    }

    int size(){ return _size; }

};

#include <iostream>
using namespace std;

int main()
{

}