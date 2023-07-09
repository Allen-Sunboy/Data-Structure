#include <iostream>
using namespace std;

const int MAXN = 5000003;

long long x[MAXN];
long long y[MAXN];

long long an[MAXN]; //临时存放
long long bn[MAXN]; //临时存放

int n;

long long sum = 0; //顺序对的数目

void mergeXY(long long x[], long long y[], int l, int mid, int h)
{
    int i = l, j = mid + 1, k = l;
    while(i <= mid && j <= h)
    {
        if(x[i] > x[j])
        {
            an[k] = x[j];
            bn[k] = y[j];
            k++;
            j++;
        }
        else
        {
            an[k] = x[i];
            bn[k] = y[i];
            k++;
            i++;
        }
    }
    while(i <= mid)
    {
        an[k] = x[i];
        bn[k] = y[i];
        k++;
        i++;
    }
    while(j <= h)
    {
        an[k] = x[j];
        bn[k] = y[j];
        k++;
        j++;
    }
    for(int i = l; i <= h; i++)
    {
        x[i] = an[i];
        y[i] = bn[i];
    }

}

void mergeSortXY(long long x[], long long y[], int l, int h)
{
    if(l >= h)
    {
        return;
    }
    int mid = (l + h) / 2;
    mergeSortXY(x, y, l, mid);
    mergeSortXY(x, y, mid+1, h);
    mergeXY(x, y, l, mid, h);
}

void mergeY(long long y[], int l, int mid, int h)
{
    int i = l, j = mid+1, k = l;
    while(i <= mid && j <= h)
    {
        if(y[i] < y[j])
        {
            an[k++] = y[i++];
            sum += h - j + 1;
        }
        else
        {
            an[k++] = y[j++];
        }      
    }
    while(i <= mid)
        an[k++] = y[i++];
    while(j <= h)
        an[k++] = y[j++];
    for(int i = l; i <= h; i++)
        y[i] = an[i];
}

void mergeSortY(long long y[], int l, int h)
{
    if(l >= h)
    {
        return;
    }
    int mid = (l + h) / 2;
    mergeSortY(y, l, mid);
    mergeSortY(y, mid+1, h);
    mergeY(y, l, mid, h);
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%lld%lld", &x[i], &y[i]);
    }
    mergeSortXY(x, y, 0, n-1);
    mergeSortY(y, 0, n-1);

    printf("%lld", sum);
}