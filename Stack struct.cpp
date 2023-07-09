struct Stack{
    int *data;
    int size;

    Stack(int n = 10003){ data = new int[n]; }

    ~Stack(){ delete[] data; }

    int top(){ return data[size-1]; }

    int pop(){
        size--;
        return data[size];
    }

    void push(int x){ data[size++] = x; }

};

#include <iostream>
using namespace std;

int main()
{

}