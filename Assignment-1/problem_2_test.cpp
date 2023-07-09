#include <iostream>
using namespace std;

const int MAXN = 1700000;
int a[MAXN];

int size = 0;
int n, m; //n是车厢数，m是容量

int print[MAXN * 2]; //操作序列，0表示push，1表示pop

void push(int x)
{
    a[size] = x;
    size++;
}

void pop()
{
    a[size] = 0;
    size--;
}

int main()
{
    // setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    // setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);

    scanf("%d%d", &n, &m);

    int p_in = 1;
    int p = 0;

    int k;
    for(int i = 0; i < n; i++)
    {
        // scanf("%d", &k);
        cin >> k;
        while(size == 0 || k != a[size-1])
        {
            if(size < m)
            {
                push(p_in++);
                print[p++] = 0;
            }
            else
            {
                printf("No\n");
                return 0;
            }
        }
        pop();
        print[p++] = 1;
    }

    for(int i = 0; i < p; i++)
    {
        if(print[i] == 0)
        {
            // printf("push\n");
            cout << "push\n";
        }
        else
        {
            // printf("pop\n");
            cout << "pop\n";

        }
    }
}