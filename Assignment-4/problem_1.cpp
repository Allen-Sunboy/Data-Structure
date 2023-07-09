#include <iostream>
#include <cstring>
using namespace std;

//阶乘
int f[16];
void fact()
{
    f[0] = 1;
    for(int i = 1; i <= 15; i++)
        f[i] = f[i-1] * i;
}
//f[8] = 40320

const int total = 40320;

const int INF = 0x3f3f3f3f;

//康托展开
int Cantor(int a[], int n){
    // fact();
    int ans = 1;
    for(int i = 0; i < n; i++)
    {
        int tmp = 0;
        for(int j = i + 1; j < n; j++)
            if(a[i] > a[j])
                tmp++;
        ans += tmp * f[n - i - 1];
    }
    return ans;
}

//逆康托展开
void revCantor(int temp[], int x, int n){
    // fact();
    bool visit[18];
    memset(visit, 0, sizeof(visit));

    int k;
    int r = x - 1;
    for(int i = 0; i < n; i++)
    {
        k = r / f[n - i - 1];
        r %= f[n - i - 1];
        for(int j = 1; j <= n; j++)
        {
            if(!visit[j] && !(k--))
            {
                visit[j] = 1;
                temp[i] = j;
                break;
            }
        }
    }
}

//若状态x通过A方式变为y，则ARev[y] = x，即存储的是反向操作的结果，B，C同理
int ARev[40400];
int BRev[40400];
int CRev[40400];

bool visitA[40400];
bool visitB[40400];
bool visitC[40400];

void formA(){
    for(int i = 1; i <= total; i++)
    {
        if(visitA[i] == 0)
        {
            int temp[9];
            revCantor(temp, i, 8);

            for(int j = 0, k = 7; j < k; j++, k--)
                swap(temp[j], temp[k]);
            
            int res = Cantor(temp, 8);

            ARev[i] = res;
            ARev[res] = i;
            
            visitA[i] = 1;
            visitA[res] = 1;
        }
    }
}

void formB(){
    for(int i = 1; i <= total; i++)
    {
        if(visitB[i] == 0)
        {
            int temp[9];
            revCantor(temp, i, 8);

            swap(temp[3], temp[2]); swap(temp[2], temp[1]); swap(temp[1], temp[0]);
            swap(temp[4], temp[5]); swap(temp[5], temp[6]); swap(temp[6], temp[7]);

            int res = Cantor(temp, 8);

            BRev[res] = i;
            visitB[i] = 1;
        }
    }
}

void formC(){
    for(int i = 1; i <= total; i++)
    {
        if(visitC[i] == 0)
        {
            int temp[9];
            revCantor(temp, i, 8);

            swap(temp[1], temp[6]); swap(temp[6], temp[2]); swap(temp[5], temp[6]);

            int res = Cantor(temp, 8);

            CRev[res] = i;
            visitC[i] = 1;
        }
    }
}

class Queue{
private:
    int *data;
    int front = -1;
    int rear = -1;
public:
    Queue(int n = 10003){
        data = new int[n];
    }

    bool empty(){
        return (rear == -1 && front == -1);
    }

    void enqueue(int x){
        if(empty())
        {
            front = 0;
            rear = 0;
            data[rear] = x;
        }
        else
        {
            ++rear;
            data[rear] = x;
        }
    }
    
    int size(){
        if(empty())
            return 0;
        else
            return rear - front + 1;
    }

    int dequeue(){
        if(empty())
            return 0;
        else if(front == rear)
        {
            int temp = front;
            front = -1;
            rear = -1;
            return data[temp];
        }
        else
        {
            ++front;
            return data[front-1];
        }
    }

};

//从初始状态即状态1到其他状态的最小距离
int reach[40400];

bool visit[40400];

Queue a(50400);

//从初始状态1开始搜索
void BFS(){
    for(int i = 1; i <= total; i++)
        reach[i] = INF;
    
    reach[1] = 0;
    a.enqueue(1);
    visit[1] = 1;

    while(a.size() != 0)
    {
        int f = a.dequeue();

        if(visit[ARev[f]] == 0)
        {
            a.enqueue(ARev[f]);
            reach[ARev[f]] = reach[f] + 1;
            visit[ARev[f]] = 1;
            
        }
        if(visit[BRev[f]] == 0)
        {
            a.enqueue(BRev[f]);
            reach[BRev[f]] = reach[f] + 1;
            visit[BRev[f]] = 1;
        }
        if(visit[CRev[f]] == 0)
        {
            a.enqueue(CRev[f]);
            reach[CRev[f]] = reach[f] + 1;
            visit[CRev[f]] = 1;
        }
    }

}

int n;

int main()
{
    fact();
    formA();
    formB();
    formC();
    BFS();

    cin >> n;
    int a[9];
    int c;
    while(n--)
    {
        for(int i = 0; i < 8; i++)
            cin >> a[i];
        c = Cantor(a, 8);
        
        cout << (reach[c] == INF ? -1 : reach[c]) << endl;
    }
}