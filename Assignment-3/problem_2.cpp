const int MAXN = 1000003;

class Stack{
private:
    int *data;
    int _size;
public:
    Stack(int n = MAXN){
        data = new int[n];
    }

    int top(){
        return data[_size-1];
    }

    int pop(){
        _size--;
        return data[_size];
    }

    void push(int x){
        data[_size++] = x;
    }

    ~Stack(){
        delete[] data;
    }

    int size(){
        return _size;
    }

};
Stack s;

//边，用链表存储
struct Edge{
    int u, v; // u -> v
    Edge *succEdge; //其下一条边
    Edge(int uu, int vv): u(uu), v(vv){}
};

struct Vertex{
    int indeg; //入度
    int length = 1; //标记，由1开始计数
    Edge *succEdge; //顶点的出边，用链表存储
};

Vertex vertex[MAXN];

int n, m;

#include <iostream>
using namespace std;
int main()
{
    cin >> n >> m;
    int a, b;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &a, &b);
        Edge *newEdge = new Edge(a, b);
        vertex[b].indeg++;
        newEdge->succEdge = vertex[a].succEdge;
        vertex[a].succEdge = newEdge;
    }

    int result = 0;

    //拓扑排序算法
    for (int i = 1; i <= n; i++)
    {
        //入度为0的点先入栈
        if (vertex[i].indeg == 0)
            s.push(i);
    }
    while (s.size() != 0)
    {
        Vertex topV = vertex[s.pop()];
        Edge *p = topV.succEdge;
        //遍历栈顶的点的所有出边
        while (p != nullptr)
        {
            //更新每个顶点的标记的长度
            vertex[p->v].length = max(topV.length+1, vertex[p->v].length);
            //更新最终结果
            result = max(result, vertex[p->v].length);
            vertex[p->v].indeg--;
            if (vertex[p->v].indeg == 0)
            {
                s.push(p->v);
            }
            //遍历
            p = p->succEdge;
        }
    }

    cout << result;
}
