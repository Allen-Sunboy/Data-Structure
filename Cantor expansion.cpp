int f[16];
void fact()
{
    f[0] = 1;
    for(int i = 1; i <= 15; i++)
        f[i] = f[i-1] * i;
}

long long F[21];
void Fact()
{
    F[0] = 1;
    for(int i = 1; i <= 20; i++)
        F[i] = F[i-1] * i;
}

int Cantor(int a[], int n){
    fact();
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

void revCantor(int temp[], int x, int n){
    fact();
    bool visit[25];
    for(int i = 0; i < 25; i++)
        visit[i] = 0;
    int r = x - 1;
    for(int i = 0; i < n; i++)
    {
        int k = r / f[n - i - 1];
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

#include <iostream>
using namespace std;

int main()
{
    
}