#define DEFAULT_CAPACITY 3
template <typename T>
class Vector{
protected:
    int _size;
    int _capacity;
    T* _elem;
public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0){
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }

    void copyFrom(const T *A, int lo, int hi){
        _elem = new T[_capacity = 2 * (hi - lo)];
        _size = 0;
        while (lo < hi)
            _elem[_size++] = A[lo++];
    }

    Vector(const T *A, int n){
        copyFrom(A, 0, n);
    }

    Vector<T> &operator=(const Vector<T> &V){
        if (_elem)
            delete[] _elem;
        copyFrom(V._elem, 0, V.size());
        return *this;
    }

    ~Vector(){
        delete[] _elem;
    }

    T &operator[](int r) const{
        return _elem[r];
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

    int insert(int r, const T &e){
        expand();
        for (int i = _size; i > r; --i)
            _elem[i] = _elem[i-1];
        _elem[r] = e;
        ++_size;
        return r;
    }

    int append(const T &e){
        return insert(_size, e);
    }

    int remove(int lo, int hi){
        if (lo == hi)
            return 0;
        while (hi < _size)
            _elem[lo++] = _elem[hi++];
        _size = lo;
        return hi - lo;
    }

    T remove(int r){
        T e = _elem[r];
        remove(r, r+1);
        return e;
    }

    int size(){
        return _size;
    }
};

#include <iostream>
using namespace std;

const int MAXN = 10003;

int Queue[MAXN]; //队列

int front = -1;
int rear = -1;

bool empty()
{
    return(front == -1 && rear == -1);
}

int size()
{
    if (empty())
        return 0;
    else
        return rear - front + 1;
}

void enqueue(int x)
{
    if (empty())
    {
        rear = 0;
        front = 0;
        Queue[0] = x;
    }
    else
    {
        ++rear;
        Queue[rear] = x;
    }
}

int dequeue()
{
    int x;
    if (empty())
    {
        return 0;
    }
    else if (front == rear)
    {
        x = front;
        front = -1;
        rear = -1;
        return Queue[x];
    }
    else
    {   x = front;
        ++front;
        return Queue[x];
    }
}

int n, m;


Vector<int> edge[MAXN];

int Type[MAXN]; //每个小镇的波段，用1和2表示

int main()
{

    cin >> n >> m;
    int a, b;
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d", &a, &b);
        edge[a].append(b);
        edge[b].append(a);
    }
    int p = 1;
    enqueue(1);
    Type[1] = 1;

    while (p <= n)
    {
        int f = dequeue();
        int t = Type[f];
        for (int i = 0; i < edge[f].size(); ++i)
        {
            int p2 = edge[f][i];
            if (!Type[p2])
            {
                enqueue(p2);
                Type[p2] = (t == 1 ? 2 : 1);
            }
            else if (Type[p2] == t)
            {
                cout << -1 << endl;
                return 0;
            }
        }
        ++p;
    }
    cout << 1 << endl;

}