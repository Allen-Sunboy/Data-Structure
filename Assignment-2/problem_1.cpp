#include <iostream>
using namespace std;

//点的坐标的最大值
const int MAXP = 10000003;

int n, m;
bool check[MAXP];
int total[MAXP];
int l, r, x;

int main()
{
    cin >> n >> m;
    int p;
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &p);
        check[p] = 1;
        total[p] = 1;
    }
    for(int i = 1; i < MAXP; i++)
        total[i] += total[i-1];
    for(int i = 0; i < m; i++)
    {
        scanf("%d%d", &l, &r);
        x = total[r] - total[l];
        printf("%d\n", (check[l] ? x+1: x));
    }
}